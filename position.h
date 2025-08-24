#ifndef POSITION_H
#define POSITION_H
struct Position
{
    int x = 0, y = 0; // Значения по умолчанию
    Position() = default; // Явно разрешаем конструктор по умолчанию
    Position(int r_x, int r_y) : x(r_x), y(r_y) {}
};
#endif // POSITION_H


