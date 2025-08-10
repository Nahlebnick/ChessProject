#include "board.h"

board::board(QWidget *parent)
    : QWidget(parent)
{
    setFixedSize(8*64, 8*64);
    initBoard();
}

void board::paintEvent(QPaintEvent * )
{
    QPainter painter(this);

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            int x = cells[i][j].get_x();
            int y = cells[i][j].get_y();
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

    painter.setBrush(QBrush(Qt::red));
    painter.setPen(Qt::NoPen);
    for (int i = 1; i < m_posible_moves.size(); i++)
    {
        int x = cells[m_posible_moves[i].x][m_posible_moves[i].y].get_x();
        int y = cells[m_posible_moves[i].x][m_posible_moves[i].y].get_y();
        painter.drawRect(x+22, y+22, 20, 20);
    }
}

void board::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton)
    {
        UndoSelection();
        qDebug() << "White king at cell " << white_king_position.x << white_king_position.y;
        qDebug() << "Black king at cell " << black_king_position.x << black_king_position.y;
        update();
        return;
    }
    int curr_x = event->pos().x() / 64;
    int curr_y = event->pos().y() / 64;

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

void board::initBoard()
{
    for (int i =0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if ((i+j)%2==0) cells[i][j] = Cell(i*64, j*64, QColor::fromRgb(217, 160, 102));
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

    cells[4][7].m_piece = new Queen(PlayerType::white);
    cells[4][0].m_piece = new Queen(PlayerType::black);

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
                    if (current_player == PlayerType::black)
                    {
                        if (x.x == white_king_position.x && x.y == white_king_position.y)
                        {
                            qDebug() << "Check for white king!";
                            white_king_checked = true;
                            black_king_checked = false;
                            return;
                        }
                    }
                    else
                    {
                        if (x.x == black_king_position.x && x.y == black_king_position.y)
                        {
                            qDebug() << "Check for black king!";
                            black_king_checked = true;
                            white_king_checked = false;
                            return;
                        }
                    }
                }
            }
        }
    }
    white_king_checked = false;
    black_king_checked = false;
}

void board::CheckPieceMove(int curr_x, int curr_y)
{
    // Если на целевой клетке есть фигура (противника), удаляем её
    if (cells[curr_x][curr_y].m_piece != nullptr)
    {
        delete cells[curr_x][curr_y].m_piece;
        cells[curr_x][curr_y].m_piece = nullptr;
    }

    // Перемещаем фигуру на новую клетку
    cells[curr_x][curr_y].m_piece = cells[m_x_selected][m_y_selected].m_piece;
    cells[curr_x][curr_y].m_piece->moved(false);

    // Очищаем старую клетку
    cells[m_x_selected][m_y_selected].m_piece = nullptr;

    if (cells[curr_x][curr_y].m_piece->get_pawn_type() == PawnType::king)
    {
        if (current_player == PlayerType::white) white_king_position = Position(curr_x, curr_y);
        else black_king_position = Position(curr_x, curr_y);
    }

    if (current_player == PlayerType::white) qDebug() << "Ходила белая фигура!";
    else qDebug() << "Ходила чёрная фигура!";
    CheckForCheck();
}

void board::SelectPiece(int curr_x, int curr_y)
{
    if (cells[curr_x][curr_y].m_piece != nullptr && cells[curr_x][curr_y].m_piece->get_player_type()==current_player)
    {
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
    Cell tmp_cells[8][8];
    cloneBoard(tmp_cells);

    Position tmp_white_king_pos = white_king_position;
    Position tmp_black_king_pos = black_king_position;

    // Если на целевой клетке есть фигура (противника), удаляем её
    if (tmp_cells[pos.x][pos.y].m_piece != nullptr)
    {
        delete tmp_cells[pos.x][pos.y].m_piece;
        tmp_cells[pos.x][pos.y].m_piece = nullptr;
    }

    // Перемещаем фигуру на новую клетку
    /*tmp_cells[pos.x][pos.y].m_piece = tmp_cells[m_x_selected][m_y_selected].m_piece;
    tmp_cells[pos.x][pos.y].m_piece->moved(false);

    // Очищаем старую клетку
    delete tmp_cells[m_x_selected][m_y_selected].m_piece;
    tmp_cells[m_x_selected][m_y_selected].m_piece = nullptr;

    if (tmp_cells[pos.x][pos.y].m_piece->get_pawn_type() == PawnType::king)
    {
        if (current_player == PlayerType::white) tmp_white_king_pos = Position(pos.x, pos.y);
        else tmp_black_king_pos = Position(pos.x, pos.y);
    }

    bool tmp_white_king_checked = white_king_checked;
    bool tmp_black_king_checked = black_king_checked;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (tmp_cells[i][j].m_piece != nullptr && tmp_cells[i][j].m_piece->get_player_type() == current_player)
            {
                QVector<Position> poses_that_will_be_attacked;
                poses_that_will_be_attacked.push_back(Position(i, j));
                tmp_cells[i][j].m_piece->howToMove(poses_that_will_be_attacked, cells);
                for (auto x : std::as_const(poses_that_will_be_attacked))
                {
                    if (current_player == PlayerType::black)
                    {
                        if (x.x == tmp_white_king_pos.x && x.y == tmp_white_king_pos.y)
                        {
                            tmp_white_king_checked = true;
                            break;
                        }
                    }
                    else
                    {
                        if (x.x == tmp_black_king_pos.x && x.y == tmp_black_king_pos.y)
                        {
                            tmp_black_king_checked = true;
                            break;
                        }
                    }
                }
                if (tmp_white_king_checked || tmp_black_king_checked) break;
            }
        }
    }
    if (tmp_black_king_checked && current_player == PlayerType::black)
    {
        return false;
    }
    else if(tmp_white_king_checked && current_player == PlayerType::white)
    {
        return false;
    }
    else
    {
        return true;
    }*/
    return true;
}

void board::validateMoves()
{
    int i = 1;
    while (i < m_posible_moves.size())
    {
        if (!isMoveValid(m_posible_moves[i]))
        {
            m_posible_moves.erase(m_posible_moves.begin()+i);
        }
        else
        {
            i++;
        }
    }
}


// Новый метод клонирования доски
void board::cloneBoard(Cell tmp_cells[8][8]) const
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            tmp_cells[i][j] = Cell(cells[i][j]);
        }
    }
}


board::~board()
{
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            delete cells[i][j].m_piece;
}
