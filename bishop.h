#ifndef BISHOP_H
#define BISHOP_H

#include "piece.h"

class Bishop : public Piece
{
public:
    Bishop(PlayerType player, QObject *parent = nullptr);

    Bishop(const Bishop& obj) : Piece(obj.owner, PawnType::pawn)
    {
        this->type = obj.type;
        this->imagePath = obj.imagePath;
        this->first_move = obj.first_move;
        this->ableToCastle = obj.ableToCastle;
    };

    void howToMove(QVector<Position>&, Cell cells[8][8]) override;

    Piece* clone() override
    {
        return new Bishop(*this);
    }
};

#endif // BISHOP_H
