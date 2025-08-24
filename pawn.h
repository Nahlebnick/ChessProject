#ifndef PAWN_H
#define PAWN_H

#include "piece.h"

class Pawn : public Piece
{
public:
    Pawn(PlayerType player, QObject *parent = nullptr);

    Pawn(const Pawn& obj) : Piece(obj.owner, PawnType::pawn)
    {
        this->type = obj.type;
        this->imagePath = obj.imagePath;
        this->first_move = obj.first_move;
        this->ableToCastle = obj.ableToCastle;
    };

    void howToMove(QVector<Position>&, Cell cells[8][8]) override;

    // Добавляем метод clone для клонирования объекта
    Piece* clone() override
    {
        return new Pawn(*this);
    }

};

#endif // PAWN_H
