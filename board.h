#ifndef BOARD_H
#define BOARD_H

#include <QObject>
#include <QPainter>
#include <QVector>
#include <QMouseEvent>
#include <qcolor.h>
#include "piece.h"
#include "pawn.h"
#include "knight.h"
#include "queen.h"
#include "bishop.h"
#include "rook.h"
#include "Cell.h"
#include <algorithm>

class board : public QObject
{
    Q_OBJECT
    Cell cells[8][8];
    bool piece_active;

    Piece *white_pieces[16];
    Piece *black_pieces[16];
    PlayerType current_player;
public:
    board(QObject *parent = nullptr);
    void draw(QPainter *painter);
    void checkMouse(QMouseEvent *pe);
    int m_x_selected, m_y_selected;
private:
    void initBoard();
    QVector<Position> m_posible_moves;
    void UndoSelection();

    void CheckPieceMove(int, int);
    void SelectPiece(int, int);

    void ValidateMoves();

    void changeCurrentPlayer();
signals:
};

#endif // BOARD_H
