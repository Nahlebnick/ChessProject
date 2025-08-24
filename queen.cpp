#include "queen.h"
#include "Cell.h"

Queen::Queen(PlayerType player, QObject *parent)
    : Piece(player, PawnType::queen) {
    imagePath = (player == PlayerType::white) ? QString("C:/Programming/ChessProject/gfx/white_queen.png") :
                    QString("C:/Programming/ChessProject/gfx/black_queen.png");
}

void Queen::howToMove(QVector<Position> &pos, Cell cells[8][8])
{
    if (pos.size() == 1)
    {
        vertical_and_horizontal_move(pos, cells);
        diagonal_move(pos, cells);
    }
}
