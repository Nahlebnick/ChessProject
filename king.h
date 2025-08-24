#ifndef KING_H
#define KING_H

#include "piece.h"

class King : public Piece
{
public:
    King(PlayerType player, QObject *parent = nullptr);

    King(const King& obj) : Piece(obj.owner, PawnType::pawn)
    {
        this->type = obj.type;
        this->imagePath = obj.imagePath;
        this->first_move = obj.first_move;
        this->ableToCastle = obj.ableToCastle;
    };

    void howToMove(QVector<Position>&, Cell cells[8][8]) override;

    Piece* clone() override
    {
        return new King(*this);
    }
};

#endif // KING_H
