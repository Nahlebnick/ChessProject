#include "knight.h"
#include "Cell.h"

Knight::Knight(PlayerType player, QObject *parent)
    : Piece(player, PawnType::knight) {
    imagePath = (player == PlayerType::white) ? QString("D:/Programming/QT/chess/gfx/white_knight.png") :
                    QString("D:/Programming/QT/chess/gfx/black_knight.png");
}

void Knight::howToMove(QVector<Position> &pos, Cell cells[8][8])
{
    if (pos.size() == 1)
    {
        Position new_pos(0, 0);
        new_pos.x = pos[0].x+1;       //два вверх, один влево
        new_pos.y = pos[0].y-2;
        if (IfPosCorrect(new_pos))
        {
            if (cells[new_pos.x][new_pos.y].m_piece == nullptr) pos.push_back(new_pos);
            else
            {
                if (cells[new_pos.x][new_pos.y].m_piece->get_player_type() != owner) pos.push_back(new_pos);
            }
        }

        new_pos.x = pos[0].x+1;     //два вниз, один влево
        new_pos.y = pos[0].y+2;
        if (IfPosCorrect(new_pos))
        {
            if (cells[new_pos.x][new_pos.y].m_piece == nullptr) pos.push_back(new_pos);
            else
            {
                if (cells[new_pos.x][new_pos.y].m_piece->get_player_type() != owner) pos.push_back(new_pos);
            }
        }

        new_pos.x = pos[0].x-1;
        new_pos.y = pos[0].y-2;        //два вверх, один вправо
        if (IfPosCorrect(new_pos))
        {
            if (cells[new_pos.x][new_pos.y].m_piece == nullptr) pos.push_back(new_pos);
            else
            {
                if (cells[new_pos.x][new_pos.y].m_piece->get_player_type() != owner) pos.push_back(new_pos);
            }
        }

        new_pos.x = pos[0].x-1;       //два вверх, один влево
        new_pos.y = pos[0].y+2;
        if (IfPosCorrect(new_pos))
        {
            if (cells[new_pos.x][new_pos.y].m_piece == nullptr) pos.push_back(new_pos);
            else
            {
                if (cells[new_pos.x][new_pos.y].m_piece->get_player_type() != owner) pos.push_back(new_pos);
            }
        }

        //--------------------------------------
        new_pos.x = pos[0].x+2;       //один вверх, два влево
        new_pos.y = pos[0].y-1;
        if (IfPosCorrect(new_pos))
        {
            if (cells[new_pos.x][new_pos.y].m_piece == nullptr) pos.push_back(new_pos);
            else
            {
                if (cells[new_pos.x][new_pos.y].m_piece->get_player_type() != owner) pos.push_back(new_pos);
            }
        }

        new_pos.x = pos[0].x+2;     //один вниз, два влево
        new_pos.y = pos[0].y+1;
        if (IfPosCorrect(new_pos))
        {
            if (cells[new_pos.x][new_pos.y].m_piece == nullptr) pos.push_back(new_pos);
            else
            {
                if (cells[new_pos.x][new_pos.y].m_piece->get_player_type() != owner) pos.push_back(new_pos);
            }
        }

        new_pos.x = pos[0].x-2;
        new_pos.y = pos[0].y-1;        //один вверх, два вправо
        if (IfPosCorrect(new_pos))
        {
            if (cells[new_pos.x][new_pos.y].m_piece == nullptr) pos.push_back(new_pos);
            else
            {
                if (cells[new_pos.x][new_pos.y].m_piece->get_player_type() != owner) pos.push_back(new_pos);
            }
        }

        new_pos.x = pos[0].x-2;       //один вверх, два влево
        new_pos.y = pos[0].y+1;
        if (IfPosCorrect(new_pos))
        {
            if (cells[new_pos.x][new_pos.y].m_piece == nullptr) pos.push_back(new_pos);
            else
            {
                if (cells[new_pos.x][new_pos.y].m_piece->get_player_type() != owner) pos.push_back(new_pos);
            }
        }
    }
}

