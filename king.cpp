#include "king.h"
#include "Cell.h"

King::King(PlayerType player, QObject *parent) : Piece(player, PawnType::king)
{
    imagePath = (player == PlayerType::white) ? QString("D:/Programming/QT/chess/gfx/white_king.png") :
                    QString("D:/Programming/QT/chess/gfx/black_king.png");
    ableToCastle = true;
}

void King::howToMove(QVector<Position> &pos, Cell cells[8][8])
{
    if (pos.size() == 1)
    {
        Position new_pos(0, 0);
        for (int i = -1; i < 2; i++)
        {
            new_pos.x = pos[0].x + i;
            new_pos.y = pos[0].y+1;
            if (IfPosCorrect(new_pos))
            {
                if (cells[new_pos.x][new_pos.y].m_piece != nullptr)
                {
                    if (cells[new_pos.x][new_pos.y].m_piece->get_player_type() != owner) pos.push_back(new_pos);
                }
                else
                {
                    pos.push_back(new_pos);
                }
            }


            new_pos.x = pos[0].x + i;
            new_pos.y = pos[0].y-1;
            if (IfPosCorrect(new_pos))
            {
                if (cells[new_pos.x][new_pos.y].m_piece != nullptr)
                {
                    if (cells[new_pos.x][new_pos.y].m_piece->get_player_type() != owner) pos.push_back(new_pos);
                }
                else
                {
                    pos.push_back(new_pos);
                }
            }
        }

        new_pos.y = pos[0].y;
        new_pos.x = pos[0].x+1;
        if (IfPosCorrect(new_pos))
        {
            if (cells[new_pos.x][new_pos.y].m_piece != nullptr)
            {
                if (cells[new_pos.x][new_pos.y].m_piece->get_player_type() != owner) pos.push_back(new_pos);
            }
            else
            {
                pos.push_back(new_pos);
            }
        }

        new_pos.y = pos[0].y;
        new_pos.x = pos[0].x-1;
        if (IfPosCorrect(new_pos))
        {
            if (cells[new_pos.x][new_pos.y].m_piece != nullptr)
            {
                if (cells[new_pos.x][new_pos.y].m_piece->get_player_type() != owner) pos.push_back(new_pos);
            }
            else
            {
                pos.push_back(new_pos);
            }
        }

        /*if (ableToCastle)
        {
            bool able00 = true;
            for (int x = pos[0].x-1; x >= pos[0].x-2; x--)
            {
                if (cells[x][pos[0].y].m_piece != nullptr)
                {
                    able00 = false;
                    qDebug() << "Короткая рокировка невозможна!";
                    break;
                }
            }
            if (able00)
            {
                if (cells[pos[0].x-3][pos[0].y].m_piece != nullptr && cells[pos[0].x-3][pos[0].y].m_piece->get_pawn_type() == PawnType::rook &&
                    cells[pos[0].x-3][pos[0].y].m_piece->ableToCastle)
                {
                    new_pos.x = pos[0].x-2;
                    new_pos.y = pos[0].y;
                    pos.push_back(new_pos);
                    qDebug() << "Короткая рокировка возможна!";
                }
            }
        }*/
    }
}
