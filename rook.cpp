#include "rook.h"

Rook::Rook(PlayerType player, QObject *parent)
    : Piece(player, PawnType::rook) {
    imagePath = (player == PlayerType::white) ? QString("D:/Programming/QT/chess/gfx/white_rook.png") :
                    QString("D:/Programming/QT/chess/gfx/nigga_rook.png");
}

void Rook::howToMove(QVector<Position> &pos)
{
    if (pos.size() == 1)
    {
        vertical_and_horizontal_move(pos);
    }
}

