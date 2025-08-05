#include "board.h"

board::board(QObject *parent)
    : QObject{parent}
{
    initBoard();
}

void board::draw(QPainter *painter)
{
    for (int i =0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            int x = cells[i][j].get_x();
            int y = cells[i][j].get_y();
            painter->setBrush(QBrush(QColor(cells[i][j].get_color())));
            if (cells[i][j].isSelected())
            {
                painter->setPen(QPen(Qt::yellow, 4, Qt::SolidLine));
                painter->drawRect(x+2, y+2, 60, 60);
            }
            else
            {
                painter->setPen(Qt::NoPen);
                painter->drawRect(x, y, 64, 64);
            }

            if (cells[i][j].m_piece)
            {
                cells[i][j].m_piece->draw(painter, x, y);
            }
        }
    }

    painter->setBrush(QBrush(Qt::red));
    painter->setPen(Qt::NoPen);
    for (int i = 1; i < m_posible_moves.size(); i++)
    {      
        int x = cells[m_posible_moves[i].x][m_posible_moves[i].y].get_x();
        int y = cells[m_posible_moves[i].x][m_posible_moves[i].y].get_y();
        painter->drawRect(x+22, y+22, 20, 20);
    }
}

void board::checkMouse(QMouseEvent *pe)
{
    int curr_x, curr_y;
    curr_x = pe->pos().x();
    curr_x /= 64;
    curr_y = pe->pos().y();
    curr_y /= 64;

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
        white_pieces[i] = new Pawn(PlayerType::black);
        cells[i][1].m_piece = white_pieces[i];
        black_pieces[i] = new Pawn(PlayerType::white);
        cells[i][6].m_piece = black_pieces[i];
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

void board::CheckPieceMove(int curr_x, int curr_y)
{
    qDebug() << "Фигура ходит на поле [" << curr_x << curr_y << "]";
    cells[curr_x][curr_y].m_piece = cells[m_x_selected][m_y_selected].m_piece;
    cells[curr_x][curr_y].m_piece->moved();
    //qDebug() << m_x_selected << m_y_selected;
    cells[m_x_selected][m_y_selected].m_piece = nullptr;
    changeCurrentPlayer();
    UndoSelection();
}

void board::SelectPiece(int curr_x, int curr_y)
{
    if (cells[curr_x][curr_y].m_piece != nullptr && cells[curr_x][curr_y].m_piece->get_player_type()==current_player)
    {
        cells[curr_x][curr_y].setSelected();
        m_x_selected = curr_x;
        m_y_selected = curr_y;

        m_posible_moves.push_back(Position(curr_x, curr_y));
        switch (cells[curr_x][curr_y].m_piece->get_pawn_type()) {
        case PawnType::pawn: qDebug() << "pawn";
            break;
        case PawnType::king: qDebug() << "king";
            break;
        case PawnType::knight: qDebug() << "knight";
            break;
        case PawnType::queen: qDebug() << "queen";
            break;
        case PawnType::bishop: qDebug() << "bishop";
            break;
        case PawnType::rook: qDebug() << "rook";
            break;
        default:
            break;
        };

        cells[curr_x][curr_y].m_piece->howToMove(m_posible_moves);
        ValidateMoves();
        for (auto x : std::as_const(m_posible_moves))
        {
            qDebug() << x.x << x.y;
        }
        piece_active = true;
    }
    else
    {
        qDebug() << "No piece on cell [" << curr_x << curr_y << "] or another player should move";
        UndoSelection();
    }
}

void board::ValidateMoves()
{
    int i = 1;
    while(i < m_posible_moves.size())
    {
        Position pos(m_posible_moves[i]);
        if (cells[pos.x][pos.y].m_piece != nullptr)
        {
            if (cells[pos.x][pos.y].m_piece->get_player_type() == cells[m_x_selected][m_y_selected].m_piece->get_player_type())
            {
                qDebug() << "На клетке [" << pos.x << pos.y << "] есть фигруа, того же цвета!";
                m_posible_moves.erase(m_posible_moves.begin()+i);
                continue;
            }
            else
            {
                qDebug() << "На клетке [" << pos.x << pos.y << "] есть фигруа, другого цвета!";
            }
        }
        i++;
    }
}

void board::changeCurrentPlayer()
{
    current_player = (current_player == PlayerType::white) ? PlayerType::black : PlayerType::white;
}
