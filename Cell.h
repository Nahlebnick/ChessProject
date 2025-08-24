#ifndef CELL_H
#define CELL_H
#include "piece.h"
#include <qcolor.h>
class Cell
{
    int m_x;
    int m_y;
    QColor m_color;
    bool m_selected;

public:
    Cell() {m_x = 0; m_y=0; m_color = Qt::red;}
    Cell(int x, int y, QColor color) : m_x(x), m_y(y), m_color(color), m_selected(false) {};


    int get_x() {return m_x;}
    int get_y() {return m_y;}

    bool isSelected() {return m_selected;}
    void setSelected() {
        m_selected = !m_selected;
        //qDebug() << m_selected;
    }
    Piece *m_piece;
    QColor& get_color() {return m_color;}

    bool white_enPassant = false;
    bool black_enPassant = false;
};
#endif // CELL_H
