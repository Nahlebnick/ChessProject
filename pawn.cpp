#include "pawn.h"
#include "Cell.h"

Pawn::Pawn(PlayerType player, QObject *parent)
    : Piece(player, PawnType::pawn) {
    imagePath = (player == PlayerType::white) ? QString("D:/Programming/QT/chess/gfx/white_pawn.png") :
                    QString("D:/Programming/QT/chess/gfx/black_pawn.png");
}

void Pawn::howToMove(QVector<Position> &pos, Cell cells[8][8])
{
    if (pos.size() == 1)
    {
        int dir = (owner == PlayerType::white) ? 1 : -1;
        if (pos[0].y != 0)
        {
            Position new_pos(0, 0);
            new_pos.x = pos[0].x;       //Перед пешкой
            new_pos.y = pos[0].y-(dir*1);
            if (IfPosCorrect(new_pos) && cells[new_pos.x][new_pos.y].m_piece == nullptr) pos.push_back(new_pos);

            new_pos.x = pos[0].x-1;     //Забрать фигуру слева
            new_pos.y = pos[0].y-(dir*1);
            if (IfPosCorrect(new_pos) && cells[new_pos.x][new_pos.y].m_piece != nullptr
                && cells[new_pos.x][new_pos.y].m_piece->get_player_type() != owner) pos.push_back(new_pos);

            new_pos.x = pos[0].x+1;
            new_pos.y = pos[0].y-(dir*1);        //Забрать фигуру справа
            if (IfPosCorrect(new_pos) && cells[new_pos.x][new_pos.y].m_piece != nullptr
                && cells[new_pos.x][new_pos.y].m_piece->get_player_type() != owner) pos.push_back(new_pos);

            new_pos.x = pos[0].x;       //Скачок
            new_pos.y = pos[0].y-(dir*2);
            if (IfPosCorrect(new_pos) && first_move && cells[new_pos.x][new_pos.y].m_piece == nullptr && cells[new_pos.x][new_pos.y+dir].m_piece == nullptr)
            {
                pos.push_back(new_pos);
            }
        }
    }
}
