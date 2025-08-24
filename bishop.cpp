#include "bishop.h"
#include "Cell.h"

Bishop::Bishop(PlayerType player, QObject *parent)
    : Piece(player, PawnType::bishop) {
    imagePath = (player == PlayerType::white) ? QString("C:/Programming/ChessProject/gfx/white_bishop.png") :
    QString("C:/Programming/ChessProject/gfx/black_bishop.png");
}

void Bishop::howToMove(QVector<Position> &pos, Cell cells[8][8])
{
    if (pos.size() == 1)
    {
        diagonal_move(pos, cells);
    }
}


