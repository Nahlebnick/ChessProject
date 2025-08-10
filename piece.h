#ifndef PIECE_H
#define PIECE_H

#include <QObject>
#include <QPainter>
#include <QVector>
#include <QDebug>
#include "position.h"
#include "settings.h"

enum class PawnType {
    king,
    queen,
    rook,
    bishop,
    knight,
    pawn
};

enum class PlayerType {
    black,
    white
};

class Cell;  // forward declaration

class Piece : public QObject
{
    Q_OBJECT

protected:
    PawnType type;
    bool first_move;
    QString imagePath;
    PlayerType owner;

public:
    bool ableToCastle;
    Piece(PlayerType, PawnType, QObject *parent = nullptr);
    QString& get_path() { return imagePath; }
    void draw(QPainter *painter, int x, int y);
    virtual void howToMove(QVector<Position>&, Cell cells[8][8]) = 0;

    // Добавляем виртуальный метод clone
    virtual Piece* clone() const = 0;

    void moved(bool f) { first_move = f;}
    PlayerType get_player_type() { return owner; }
    PawnType get_pawn_type() { return type; }

    void vertical_and_horizontal_move(QVector<Position>&, Cell cells[8][8]);
    void diagonal_move(QVector<Position>&, Cell cells[8][8]);

    bool IfPosCorrect(Position);
};

#endif // PIECE_H
