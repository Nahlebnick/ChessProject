#ifndef KNIGHT_H
#define KNIGHT_H

#include "piece.h"

class Knight : public Piece
{
public:
    Knight(PlayerType player, QObject *parent = nullptr);

    Knight(const Knight& obj) : Piece(obj.owner, PawnType::pawn)
    {
        this->type = obj.type;
        this->imagePath = obj.imagePath;
        this->first_move = obj.first_move;
        this->ableToCastle = obj.ableToCastle;
    };

    void howToMove(QVector<Position>&, Cell cells[8][8]) override;

    Piece* clone() const override
    {
        return new Knight(*this);
    }
};

#endif // KNIGHT_H
