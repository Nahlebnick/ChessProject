#ifndef KNIGHT_H
#define KNIGHT_H

#include "piece.h"

class Knight : public Piece
{
public:
    Knight(PlayerType player, QObject *parent = nullptr);

    void howToMove(QVector<Position>&);
};

#endif // KNIGHT_H
