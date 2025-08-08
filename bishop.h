#ifndef BISHOP_H
#define BISHOP_H

#include "piece.h"

class Bishop : public Piece
{
public:
    Bishop(PlayerType player, QObject *parent = nullptr);

    void howToMove(QVector<Position>&, Cell cells[8][8]);
};

#endif // BISHOP_H
