#ifndef ROOK_H
#define ROOK_H

#include "piece.h"

class Rook : public Piece
{
public:
    Rook(PlayerType player, QObject *parent = nullptr);

    void howToMove(QVector<Position>&);
};

#endif // ROOK_H
