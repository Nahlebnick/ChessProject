#include "pawn.h"

Pawn::Pawn(PlayerType player, QObject *parent)
    : Piece(player, PawnType::pawn) {
    imagePath = (player == PlayerType::white) ? QString("D:/Programming/QT/chess/gfx/white_pawn.png") :
                    QString("D:/Programming/QT/chess/gfx/black_pawn.png");
}

void Pawn::howToMove(QVector<Position> &pos)
{
    if (pos.size() == 1)
    {
        int dir = (owner == PlayerType::white) ? 1 : -1;
        qDebug() << pos[0].x << pos[0].y;
        if (pos[0].y != 0)
        {
            Position new_pos(0, 0);
            new_pos.x = pos[0].x;       //Перед пешкой
            new_pos.y = pos[0].y-(dir*1);
            pos.push_back(new_pos);

            new_pos.x = pos[0].x-1;     //Забрать фигуру слева
            new_pos.y = pos[0].y-(dir*1);
            if (IfPosCorrect(new_pos)) pos.push_back(new_pos);

            new_pos.x = pos[0].x+1;
            new_pos.y = pos[0].y-(dir*1);        //Забрать фигуру справа
            if (IfPosCorrect(new_pos)) pos.push_back(new_pos);

            new_pos.x = pos[0].x;       //Скачок
            new_pos.y = pos[0].y-(dir*2);
            if (IfPosCorrect(new_pos) && first_move)
            {
                qDebug() << "First move";
                pos.push_back(new_pos);
            }
        }
    }
}
