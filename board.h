#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include <QPainter>
#include <QVector>
#include <QStack>
#include <QMouseEvent>
#include <QColor>
#include <QInputDialog>
#include "piece.h"
#include "pawn.h"
#include "knight.h"
#include "queen.h"
#include "bishop.h"
#include "rook.h"
#include "king.h"
#include "Cell.h"
#include <algorithm>

struct Move {
    Position from;
    Position to;
    Piece* movedPiece;
    Piece* capturedPiece;  // nullptr, если фигура на целевой клетке не была
    bool movedPieceFirstMove; // флаг, указывает, было ли у фигуры moved == false до хода (нужно для рокировок, пешек)
    Position prevWhiteKingPos;
    Position prevBlackKingPos;
    bool whiteKingChecked;
    bool blackKingChecked;

    bool OOO = false;
    bool OO = false;
};



class board : public QWidget
{
    Q_OBJECT

    Cell cells[8][8];
    bool piece_active;

    bool white_king_checked;
    bool black_king_checked;

    bool validate;

    PlayerType current_player;

    int m_x_selected, m_y_selected;

    bool isBoardFlipped = true;

    QVector<Position> m_posible_moves;

    QVector<Position> black_pieces_positions;
    QVector<Position> white_pieces_positions;

    Position white_king_position = Position(4, 7);
    Position black_king_position = Position(4, 0);

    Position enPassantTargetSquare = Position(-1, -1);

    QStack<Move> moves;
    QStack<Piece *> captured_figures;

public:
    explicit board(QWidget *parent = nullptr);
    ~board();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    void initBoard();
    void UndoSelection();

    void CheckForCheck();
    void CheckForMate();
    void CheckPieceMove(int, int);
    void UnmakeMove();
    void SelectPiece(int, int);

    void changeCurrentPlayer();

    bool isMoveValid(Position pos);

    void validateMoves();

    void promotePawn(int x, int y, PlayerType player);

    void toggleBoardFlip();
};

#endif // BOARD_H
