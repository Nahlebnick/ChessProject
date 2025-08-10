#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"

class Queen : public Piece
{
public:
    Queen(PlayerType player, QObject *parent = nullptr);

    Queen(const Queen& obj) : Piece(obj.owner, PawnType::pawn)
    {
        this->type = obj.type;
        this->imagePath = obj.imagePath;
        this->first_move = obj.first_move;
        this->ableToCastle = obj.ableToCastle;
    };

    void howToMove(QVector<Position>&, Cell cells[8][8]) override;

    Piece* clone() const override
    {
        return new Queen(*this);
    }
};

#endif // QUEEN_H
