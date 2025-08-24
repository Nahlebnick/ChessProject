#include "rook.h"
#include "Cell.h"

Rook::Rook(PlayerType player, QObject *parent) : Piece(player, PawnType::rook)
{
    imagePath = (player == PlayerType::white) ? QString("C:/Programming/ChessProject/gfx/white_rook.png") :
                    QString("C:/Programming/ChessProject/gfx/nigga_rook.png");
    ableToCastle = true;
}

void Rook::howToMove(QVector<Position> &pos, Cell cells[8][8])
{
    if (pos.size() == 1)
    {
        vertical_and_horizontal_move(pos, cells);
    }
}

