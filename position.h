#ifndef POSITION_H
#define POSITION_H
struct Position
{
    int x, y;
    Position(int r_x, int r_y) : x(r_x), y(r_y) {}
    //friend bool operator==(const Position&, const Position&);
};
#endif // POSITION_H

/*bool operator==(const Position& pos1, const Position& pos2)
{
    return (pos1.x == pos2.x && pos1.y == pos2.y);
}*/
