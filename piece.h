#ifndef PIECE_H
#define PIECE_H

#include <QObject>
#include <QPainter>
#include <QVector>
#include <qdebug.h>
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

class Piece : public QObject
{
    Q_OBJECT

    PawnType type;

protected:
    bool first_move;
    QString imagePath;
    PlayerType owner;
public:
    Piece(PlayerType, PawnType, QObject *parent = nullptr);
    QString& get_path() {return imagePath;}
    void draw(QPainter *painter, int x, int y);
    virtual void howToMove(QVector<Position>&)=0;
    void moved() {first_move = false; qDebug() << first_move;}
    PlayerType get_player_type() {return owner;}
    PawnType get_pawn_type() {return type;}

    void vertical_and_horizontal_move(QVector<Position>&);
    void diagonal_move(QVector<Position>&);

    bool IfPosCorrect(Position);



signals:
};

#endif // PIECE_H
