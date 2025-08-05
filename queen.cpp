#include "queen.h"

Queen::Queen(PlayerType player, QObject *parent)
    : Piece(player, PawnType::queen) {
    imagePath = (player == PlayerType::white) ? QString("D:/Programming/QT/chess/gfx/white_queen.png") :
                    QString("D:/Programming/QT/chess/gfx/black_queen.png");
}

void Queen::howToMove(QVector<Position> &pos)
{
    if (pos.size() == 1)
    {
        vertical_and_horizontal_move(pos);
        diagonal_move(pos);
    }
}
