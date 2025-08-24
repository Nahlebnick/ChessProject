#include "board.h"

board::board(QWidget *parent)
    : QWidget(parent)
{
    setFixedSize(8*64, 8*64);
    setFocusPolicy(Qt::StrongFocus);
    validate = false;
    initBoard();
}

void board::paintEvent(QPaintEvent * )
{
    QPainter painter(this);

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            //int x = (!isBoardFlipped) ? i*64 : (7-i)*64;
            //int y = (!isBoardFlipped) ? j*64 : (7-j)*64;
            int x = 64*i;
            int y = 64*j;
            if ((white_king_checked && white_king_position.x == i && white_king_position.y == j) ||
                (black_king_checked && black_king_position.x == i && black_king_position.y == j))
            {
                painter.setBrush(QBrush(Qt::blue));
            }
            else
            {
                painter.setBrush(QBrush(QColor(cells[i][j].get_color())));
            }
            if (cells[i][j].isSelected())
            {
                painter.setPen(QPen(Qt::yellow, 4, Qt::SolidLine));
                painter.drawRect(x+2, y+2, 60, 60);
            }
            else
            {
                painter.setPen(Qt::NoPen);
                painter.drawRect(x, y, 64, 64);
            }

            if (cells[i][j].m_piece)
            {
                cells[i][j].m_piece->draw(&painter, x, y);
            }
        }
    }

    QFont font = painter.font();
    font.setPointSize(14);
    painter.setFont(font);
    painter.setPen(Qt::black);

    // Горизонтальные буквы (a-h)
    for (int i = 0; i < 8; ++i)
    {
        char letter = (!isBoardFlipped) ? ('a' + i) : ('h'-i);
        int x = i * 64+52;
        int y = 14;
        painter.drawText(x, y, QString(letter));
        painter.drawText(x, y+(64*7), QString(letter));
    }

    // Вертикальные цифры (8-1) слева от доски, по центру каждой клетки
    for (int j = 0; j < 8; ++j)
    {
        int number = (!isBoardFlipped) ? (8-j) : j+1; // нумерация с 8 сверху вниз
        int x = 0; // слева от доски
        int y = j * 64 + 64 / 2 + 7;
        painter.drawText(x, y, QString::number(number));
        painter.drawText(x+(64*7), y, QString::number(number));
    }


    painter.setBrush(QBrush(Qt::red));
    painter.setPen(Qt::NoPen);
    for (int i = 1; i < m_posible_moves.size(); i++)
    {
        int x = cells[m_posible_moves[i].x][m_posible_moves[i].y].get_x();
        int y = cells[m_posible_moves[i].x][m_posible_moves[i].y].get_y();
        //qDebug() << x << y;
        painter.drawRect(x+22, y+22, 20, 20);
    }
}

void board::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton)
    {
        qApp->exit();
        //UnmakeMove();
        UndoSelection();
        update();
        return;
    }
    int curr_x = event->pos().x() / 64;
    int curr_y = event->pos().y() / 64;

    qDebug() << curr_x << curr_y;

    if (curr_x < 0 || curr_x >= 8 || curr_y < 0 || curr_y >= 8)
        return; // выход за границы доски

    if (piece_active)
    {
        bool valid = false;
        for (int i = 1; i < m_posible_moves.size(); i++)
        {
            if (curr_x == m_posible_moves[i].x && curr_y == m_posible_moves[i].y)
            {
                valid = true;
                break;
            }
        }

        if (valid)
        {
            CheckPieceMove(curr_x, curr_y);

            // Меняем игрока
            changeCurrentPlayer();
            if (white_king_checked || black_king_checked)
            {
                if (white_king_checked)
                {
                    cells[white_king_position.x][white_king_position.y].m_piece->ableToCastle = false;
                }
                else if (black_king_checked)
                {
                    cells[black_king_position.x][black_king_position.y].m_piece->ableToCastle = false;
                }
                CheckForMate();
            }
            else
            {
                if (cells[white_king_position.x][white_king_position.y].m_piece->isMoved())
                {
                    cells[white_king_position.x][white_king_position.y].m_piece->ableToCastle = true;
                }
                if (cells[black_king_position.x][black_king_position.y].m_piece->isMoved())
                {
                    cells[black_king_position.x][black_king_position.y].m_piece->ableToCastle = true;
                }
            }

            // Снимаем выделение и очищаем возможные ходы
            UndoSelection();

            cells[curr_x][curr_y].m_piece->ableToCastle = false;
        }
        else
        {
            UndoSelection();
            if (cells[curr_x][curr_y].m_piece != nullptr)
            {
                SelectPiece(curr_x, curr_y);
            }
        }
    }
    else
    {
        SelectPiece(curr_x, curr_y);
    }

    update(); // обновляем виджет для перерисовки доски и фигур
}

void board::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Left)
    {
        qDebug() << "Nazad";
        UndoSelection();
        UnmakeMove();
        update();
    }
}

void board::initBoard()
{
    for (int i =0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if ((i+j)%2==1) cells[i][j] = Cell(i*64, j*64, QColor::fromRgb(217, 160, 102));
            else cells[i][j] = Cell(i*64, j*64, QColor::fromRgb(238, 195, 154));
            cells[i][j].m_piece = nullptr;
        }
    }

    m_x_selected = -1;
    m_y_selected = -1;


    for (int i = 0; i < 8; i++)
    {
        cells[i][1].m_piece = new Pawn(PlayerType::black);
        cells[i][6].m_piece = new Pawn(PlayerType::white);
    }

    cells[0][7].m_piece = new Rook(PlayerType::white);
    cells[7][7].m_piece = new Rook(PlayerType::white);
    cells[0][0].m_piece = new Rook(PlayerType::black);
    cells[7][0].m_piece = new Rook(PlayerType::black);

    cells[2][7].m_piece = new Bishop(PlayerType::white);
    cells[5][7].m_piece = new Bishop(PlayerType::white);
    cells[2][0].m_piece = new Bishop(PlayerType::black);
    cells[5][0].m_piece = new Bishop(PlayerType::black);

    cells[1][7].m_piece = new Knight(PlayerType::white);
    cells[6][7].m_piece = new Knight(PlayerType::white);
    cells[1][0].m_piece = new Knight(PlayerType::black);
    cells[6][0].m_piece = new Knight(PlayerType::black);

    cells[3][7].m_piece = new Queen(PlayerType::white);
    cells[3][0].m_piece = new Queen(PlayerType::black);

    cells[white_king_position.x][white_king_position.y].m_piece = new King(PlayerType::white);
    cells[black_king_position.x][black_king_position.y].m_piece = new King(PlayerType::black);
    white_king_checked = false;
    black_king_checked = false;
    piece_active = false;

    current_player = PlayerType::white;
}

void board::UndoSelection()
{
    if (m_x_selected != -1 && m_y_selected != -1) cells[m_x_selected][m_y_selected].setSelected();
    m_x_selected = -1;
    m_y_selected = -1;
    piece_active = false;
    m_posible_moves.clear();
}

void board::CheckForCheck()
{
    white_king_checked = false;
    black_king_checked = false;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (cells[i][j].m_piece != nullptr && cells[i][j].m_piece->get_player_type() == current_player)
            {
                QVector<Position> poses_that_will_be_attacked;
                poses_that_will_be_attacked.push_back(Position(i, j));
                cells[i][j].m_piece->howToMove(poses_that_will_be_attacked, cells);
                for (auto x : std::as_const(poses_that_will_be_attacked))
                {
                    if (cells[i][j].m_piece->get_player_type() == PlayerType::black &&
                        x.x == white_king_position.x && x.y == white_king_position.y)
                    {
                        //qDebug() << "Check for white king!";
                        white_king_checked = true;
                        return;
                    }

                    else if (cells[i][j].m_piece->get_player_type() == PlayerType::white &&
                             x.x == black_king_position.x && x.y == black_king_position.y)
                    {
                        //qDebug() << "Check for black king!";
                        black_king_checked = true;
                        return;
                    }
                }
            }
        }
    }

}

void board::CheckForMate()
{
    bool mat = true;
    int tmp_x_selected(m_x_selected);
    int tmp_y_selected(m_y_selected);
    for (int i = 0; i < 8 && mat; i++)
    {
        for (int j= 0; j < 8 && mat; j++)
        {
            m_posible_moves.clear();
            if (cells[i][j].m_piece != nullptr && cells[i][j].m_piece->get_player_type()==current_player)
            {
                m_x_selected = i;
                m_y_selected = j;
                m_posible_moves.push_back(Position(i, j));

                cells[i][j].m_piece->howToMove(m_posible_moves, cells);

                validateMoves();
                if (m_posible_moves.size()-1 > 0)
                {
                    qDebug() << "Мата нету";
                    mat = false;
                }
            }
        }
    }
    m_x_selected = tmp_x_selected;
    m_y_selected = tmp_y_selected;
    if (mat)
    {
        qDebug() << "Мат";
    }
}

void board::CheckPieceMove(int curr_x, int curr_y)
{
    Move move;
    move.from = Position(m_x_selected, m_y_selected);
    move.to = Position(curr_x, curr_y);;
    move.movedPiece = cells[m_x_selected][m_y_selected].m_piece;

    move.capturedPiece = cells[curr_x][curr_y].m_piece;  // не удаляем!

    move.movedPieceFirstMove = move.movedPiece->isMoved();
    move.prevWhiteKingPos = white_king_position;
    move.prevBlackKingPos = black_king_position;
    move.whiteKingChecked = white_king_checked;
    move.blackKingChecked = black_king_checked;

    cells[enPassantTargetSquare.x][enPassantTargetSquare.y].white_enPassant = false;
    cells[enPassantTargetSquare.x][enPassantTargetSquare.y].black_enPassant = false;
    enPassantTargetSquare = Position(-1, -1);


    // Если пешка
    /*if (cells[m_x_selected][m_y_selected].m_piece->get_pawn_type() == PawnType::pawn)
    {
        // Проверяем, сделал ли пешка ход на 2 клетки вперед
        if (abs(curr_y - m_y_selected) == 2)
        {
            // Устанавливаем enPassantTargetSquare на клетку между началом и концом
            int ep_y = (curr_y + m_y_selected) / 2;
            enPassantTargetSquare = Position(curr_x, ep_y);
            if (current_player == PlayerType::white) cells[curr_x][ep_y].white_enPassant = true;
            else cells[curr_x][ep_y].black_enPassant = true;
        }
    }*/

    // Если на целевой клетке есть фигура (противника), удаляем её
    if (cells[curr_x][curr_y].m_piece != nullptr)
    {
        captured_figures.push(cells[curr_x][curr_y].m_piece);
        cells[curr_x][curr_y].m_piece = nullptr;
    }

    // Перемещаем фигуру на новую клетку
    cells[curr_x][curr_y].m_piece = cells[m_x_selected][m_y_selected].m_piece;
    cells[curr_x][curr_y].m_piece->moved(false);

    // Очищаем старую клетку
    cells[m_x_selected][m_y_selected].m_piece = nullptr;

    // Обработка превращения пешки
    if (!validate && cells[curr_x][curr_y].m_piece->get_pawn_type() == PawnType::pawn)
    {
        if ((cells[curr_x][curr_y].m_piece->get_player_type() == PlayerType::white && curr_y == 0) ||
            (cells[curr_x][curr_y].m_piece->get_player_type() == PlayerType::black && curr_y == 7))
        {
            promotePawn(curr_x, curr_y, cells[curr_x][curr_y].m_piece->get_player_type());
        }
    }

    move.OO = false;
    move.OOO = false;
    if (cells[curr_x][curr_y].m_piece->get_pawn_type() == PawnType::king)
    {
        if (current_player == PlayerType::white && !validate) white_king_position = Position(curr_x, curr_y);
        else if (current_player == PlayerType::black && !validate) black_king_position = Position(curr_x, curr_y);

        else if (current_player == PlayerType::black && validate) white_king_position = Position(curr_x, curr_y);
        else if (current_player == PlayerType::white && validate) black_king_position = Position(curr_x, curr_y);

        if (abs(m_x_selected-curr_x)==2 && !validate)
        {
            if (m_x_selected-curr_x == -2)
            {
                if (cells[7][curr_y].m_piece)
                {
                    cells[5][curr_y].m_piece = cells[7][curr_y].m_piece;
                    cells[5][curr_y].m_piece->moved(false);
                    cells[7][curr_y].m_piece = nullptr;
                    move.OO = true;
                }
            }
            else if (m_x_selected-curr_x == 2)
            {
                if (cells[0][curr_y].m_piece)
                {
                    cells[3][curr_y].m_piece = cells[0][curr_y].m_piece;
                    cells[3][curr_y].m_piece->moved(false);
                    cells[0][curr_y].m_piece = nullptr;
                    move.OOO = true;
                }
            }

        }
    }
    moves.push(move);

    //if (current_player == PlayerType::white) qDebug() << "Ходила белая фигура!";
    //else qDebug() << "Ходила чёрная фигура!";
    CheckForCheck();
}

void board::UnmakeMove()
{
    //qDebug() << "Nazad";
    if (moves.empty())
        return;

    Move move = moves.pop();

    // Возвращаем ходящую фигуру обратно
    cells[move.from.x][move.from.y].m_piece = move.movedPiece;

    // Возвращаем взятую фигуру обратно, если она была
    if (move.capturedPiece != nullptr)
    {
        captured_figures.pop();
    }
    cells[move.to.x][move.to.y].m_piece = move.capturedPiece;


    move.movedPiece->moved(move.movedPieceFirstMove);

    white_king_position = move.prevWhiteKingPos;
    black_king_position = move.prevBlackKingPos;
    white_king_checked = move.whiteKingChecked;
    black_king_checked = move.blackKingChecked;
    changeCurrentPlayer();

    if (move.OO)
    {
        if (cells[5][move.from.y].m_piece)
        {
            cells[7][move.from.y].m_piece = cells[5][move.from.y].m_piece;
            cells[7][move.from.y].m_piece->moved(true);
            cells[5][move.from.y].m_piece = nullptr;
        }
    }
    else if (move.OOO)
    {
        if (cells[3][move.from.y].m_piece)
        {
            cells[0][move.from.y].m_piece = cells[3][move.from.y].m_piece;
            cells[0][move.from.y].m_piece->moved(true);
            cells[3][move.from.y].m_piece = nullptr;
        }
    }

    else
    {
        return;
    }
    cells[move.from.x][move.from.y].m_piece->ableToCastle = true;

}

void board::SelectPiece(int curr_x, int curr_y)
{
    if (cells[curr_x][curr_y].m_piece != nullptr && cells[curr_x][curr_y].m_piece->get_player_type()==current_player)
    {
        //qDebug() << cells[curr_x][curr_y].m_piece->ableToCastle;
        cells[curr_x][curr_y].setSelected();
        m_x_selected = curr_x;
        m_y_selected = curr_y;

        m_posible_moves.push_back(Position(curr_x, curr_y));

        cells[curr_x][curr_y].m_piece->howToMove(m_posible_moves, cells);

        validateMoves();
        piece_active = true;
    }
    else
    {
        UndoSelection();
    }
}

void board::changeCurrentPlayer()
{
    current_player = (current_player == PlayerType::white) ? PlayerType::black : PlayerType::white;
}

bool board::isMoveValid(Position pos)
{
    bool res;
    changeCurrentPlayer();
    validate = true;

    CheckPieceMove(pos.x, pos.y);

    validate = false;
    if (current_player == PlayerType::black && white_king_checked)
    {
        res = false;
    }
    else if (current_player == PlayerType::white && black_king_checked)
    {
        res = false;
    }
    else
    {
        res = true;
    }
    UnmakeMove();

    return res;
}

void board::validateMoves()
{
    int i = 1;
    while (i < m_posible_moves.size())
    {
        if (!isMoveValid(m_posible_moves[i]))
        {
            if (cells[m_posible_moves[0].x][m_posible_moves[0].y].m_piece->get_pawn_type() == PawnType::king &&
                cells[m_posible_moves[0].x][m_posible_moves[0].y].m_piece->ableToCastle)
            {
                if (m_posible_moves[i].x == 3 && m_posible_moves[i].y == m_posible_moves[0].y)
                {
                    if (m_posible_moves[m_posible_moves.size()-1].x == 2)
                    {
                        m_posible_moves.erase(m_posible_moves.begin()+m_posible_moves.size()-1);
                    }
                    else if (m_posible_moves[m_posible_moves.size()-2].x == 2)
                    {
                        m_posible_moves.erase(m_posible_moves.begin()+m_posible_moves.size()-2);
                    }
                }
                else if (m_posible_moves[i].x == 5 && m_posible_moves[i].y == m_posible_moves[0].y)
                {
                    if (m_posible_moves[m_posible_moves.size()-1].x == 6)
                    {
                        m_posible_moves.erase(m_posible_moves.begin()+m_posible_moves.size()-1);
                    }
                    else if (m_posible_moves[m_posible_moves.size()-2].x == 6)
                    {
                        m_posible_moves.erase(m_posible_moves.begin()+m_posible_moves.size()-2);
                    }
                }
            }
            m_posible_moves.erase(m_posible_moves.begin()+i);
        }
        else
        {
            i++;
        }
    }
}

void board::promotePawn(int x, int y, PlayerType player)
{
    bool ok = false;
    QStringList pieces;
    pieces << "Queen" << "Rook" << "Bishop" << "Knight";

    QString item = QInputDialog::getItem(this, tr("Promotion"),
                                         tr("Choose piece:"), pieces, 0, false, &ok);
    if (ok && !item.isEmpty())
    {
        delete cells[x][y].m_piece;

        if (item == "Queen")
            cells[x][y].m_piece = new Queen(player);
        else if (item == "Rook")
            cells[x][y].m_piece = new Rook(player);
        else if (item == "Bishop")
            cells[x][y].m_piece = new Bishop(player);
        else if (item == "Knight")
            cells[x][y].m_piece = new Knight(player);
    }
}


board::~board()
{
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            delete cells[i][j].m_piece;


    while (!captured_figures.isEmpty())
    {
        Piece* p = captured_figures.pop();
        delete p;
    }

}
