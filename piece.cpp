#include "piece.h"

Piece::Piece(PlayerType player, PawnType pawn, QObject *parent) : owner(player), type(pawn), first_move(true)
{qDebug() << "Piece created";}

void Piece::draw(QPainter *painter, int x, int y)
{
    painter->drawImage(x, y, QImage(imagePath));
}

void Piece::vertical_and_horizontal_move(QVector<Position> &pos)
{
    //вверх
        Position new_pos(pos[0].x, pos[0].y);
        while(--new_pos.y >= 0)
        {
            pos.push_back(new_pos);
        }

        //вниз
        new_pos.x = pos[0].x;
        new_pos.y = pos[0].y;
        while(++new_pos.y <= 7)
        {
            pos.push_back(new_pos);
        }

        //влево
        new_pos.x = pos[0].x;
        new_pos.y = pos[0].y;
        while(--new_pos.x >= 0)
        {
            pos.push_back(new_pos);
        }

        //вправо
        new_pos.x = pos[0].x;
        new_pos.y = pos[0].y;
        while(++new_pos.x <= 7)
        {
            pos.push_back(new_pos);
        }
}

void Piece::diagonal_move(QVector<Position> &pos)
{
        //Налево вверх
        Position new_pos(pos[0].x, pos[0].y);
        while(--new_pos.x >= 0 && --new_pos.y >=0)
        {
            pos.push_back(new_pos);
        }

        //Налево вниз
        new_pos.x = pos[0].x;
        new_pos.y = pos[0].y;
        while(--new_pos.x >= 0 && ++new_pos.y <= 7)
        {
            pos.push_back(new_pos);
        }

        //Направо вверх
        new_pos.x = pos[0].x;
        new_pos.y = pos[0].y;
        while(++new_pos.x <= 7 && --new_pos.y >=0)
        {
            pos.push_back(new_pos);
        }

        //Направо вниз
        new_pos.x = pos[0].x;
        new_pos.y = pos[0].y;
        while (++new_pos.x <= 7 && ++new_pos.y <= 7)
        {
            pos.push_back(new_pos);
        }
}

bool Piece::IfPosCorrect(Position pos)
{
    if (pos.x >= 0 && pos.x <= 7 && pos.y >= 0 && pos.y <=7) return true;
    return false;
}


