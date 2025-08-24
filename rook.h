#ifndef ROOK_H
#define ROOK_H

#include "piece.h"

class Rook : public Piece
{
public:
    Rook(PlayerType player, QObject *parent = nullptr);

    Rook(const Rook& obj) : Piece(obj.owner, PawnType::pawn)
    {
        this->type = obj.type;
        this->imagePath = obj.imagePath;
        this->first_move = obj.first_move;
        this->ableToCastle = obj.ableToCastle;
    };

    void howToMove(QVector<Position>&, Cell cells[8][8]) override;

    Piece* clone() override
    {
        return new Rook(*this);
    }
};

#endif // ROOK_H
