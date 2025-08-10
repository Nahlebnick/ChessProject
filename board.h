#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include <QPainter>
#include <QVector>
#include <QMouseEvent>
#include <QColor>
#include "piece.h"
#include "pawn.h"
#include "knight.h"
#include "queen.h"
#include "bishop.h"
#include "rook.h"
#include "king.h"
#include "Cell.h"
#include <algorithm>

class board : public QWidget
{
    Q_OBJECT

    Cell cells[8][8];
    bool piece_active;

    bool white_king_checked;
    bool black_king_checked;

    PlayerType current_player;

    int m_x_selected, m_y_selected;
    QVector<Position> m_posible_moves;

    QVector<Position> black_pieces_positions;
    QVector<Position> white_pieces_positions;

    Position white_king_position = Position(3, 7);
    Position black_king_position = Position(3, 0);

public:
    explicit board(QWidget *parent = nullptr);
    ~board();

    // Новый метод для полного клонирования доски
    void cloneBoard(Cell tmp_cells[8][8]) const;

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    void initBoard();
    void UndoSelection();

    void CheckForCheck();

    void CheckPieceMove(int, int);
    void SelectPiece(int, int);

    void changeCurrentPlayer();

    bool isMoveValid(Position pos);

    void validateMoves();
};

#endif // BOARD_H
