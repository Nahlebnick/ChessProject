#ifndef ROOK_H
#define ROOK_H

#include "piece.h"

class Rook : public Piece
{
public:
    Rook(PlayerType player, QObject *parent = nullptr);

    void howToMove(QVector<Position>&, Cell cells[8][8]);
};

#endif // ROOK_H
