#include "bishop.h"
#include "Cell.h"

Bishop::Bishop(PlayerType player, QObject *parent)
    : Piece(player, PawnType::bishop) {
    imagePath = (player == PlayerType::white) ? QString("D:/Programming/QT/chess/gfx/white_bishop.png") :
    QString("D:/Programming/QT/chess/gfx/black_bishop.png");
}

void Bishop::howToMove(QVector<Position> &pos, Cell cells[8][8])
{
    if (pos.size() == 1)
    {
        diagonal_move(pos, cells);
    }
}


