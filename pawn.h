#ifndef PAWN_H
#define PAWN_H

#include "piece.h"

class Pawn : public Piece
{
public:
    Pawn(PlayerType player, QObject *parent = nullptr);

    void howToMove(QVector<Position>&);
};

#endif // PAWN_H
