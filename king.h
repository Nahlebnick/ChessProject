#ifndef KING_H
#define KING_H

#include "piece.h"

class King : public Piece
{
public:
    King(PlayerType, QObject *parent = nullptr);

    void howToMove(QVector<Position>&, Cell cells[8][8]);
};

#endif // KING_H
