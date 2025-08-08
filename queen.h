#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"

class Queen : public Piece
{
public:
    Queen(PlayerType player, QObject *parent = nullptr);

    void howToMove(QVector<Position>&, Cell cells[8][8]);
};

#endif // QUEEN_H
