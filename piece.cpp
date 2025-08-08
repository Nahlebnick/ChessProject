#include "piece.h"
#include "Cell.h"

Piece::Piece(PlayerType player, PawnType pawn, QObject *parent) : owner(player), type(pawn), first_move(true)
{qDebug() << "Piece created";}

void Piece::draw(QPainter *painter, int x, int y)
{
    painter->drawImage(x, y, QImage(imagePath));
}

void Piece::vertical_and_horizontal_move(QVector<Position> &pos, Cell cells[8][8])
{
    Position start = pos[0];

    // Вверх
    for (int y = start.y - 1; y >= 0; y--) {
        if (cells[start.x][y].m_piece == nullptr) {
            pos.push_back(Position(start.x, y));
        } else {
            // Есть фигура
            if (cells[start.x][y].m_piece->get_player_type() != owner) {
                pos.push_back(Position(start.x, y)); // Можно побить
            }
            break; // Преграда
        }
    }

    // Вниз
    for (int y = start.y + 1; y <= 7; y++) {
        if (cells[start.x][y].m_piece == nullptr) {
            pos.push_back(Position(start.x, y));
        } else {
            if (cells[start.x][y].m_piece->get_player_type() != owner) {
                pos.push_back(Position(start.x, y));
            }
            break;
        }
    }

    // Влево
    for (int x = start.x - 1; x >= 0; x--) {
        if (cells[x][start.y].m_piece == nullptr) {
            pos.push_back(Position(x, start.y));
        } else {
            if (cells[x][start.y].m_piece->get_player_type() != owner) {
                pos.push_back(Position(x, start.y));
            }
            break;
        }
    }

    // Вправо
    for (int x = start.x + 1; x <= 7; x++) {
        if (cells[x][start.y].m_piece == nullptr) {
            pos.push_back(Position(x, start.y));
        } else {
            if (cells[x][start.y].m_piece->get_player_type() != owner) {
                pos.push_back(Position(x, start.y));
            }
            break;
        }
    }
}


void Piece::diagonal_move(QVector<Position> &pos, Cell cells[8][8])
{
    Position start = pos[0];

    // Налево вверх
    for (int x = start.x - 1, y = start.y - 1; x >= 0 && y >= 0; --x, --y) {
        if (cells[x][y].m_piece == nullptr) {
            pos.push_back(Position(x, y));
        } else {
            if (cells[x][y].m_piece->get_player_type() != owner) {
                pos.push_back(Position(x, y));
            }
            break; // встречена фигура — дальше в этом направлении нельзя
        }
    }

    // Налево вниз
    for (int x = start.x - 1, y = start.y + 1; x >= 0 && y <= 7; --x, ++y) {
        if (cells[x][y].m_piece == nullptr) {
            pos.push_back(Position(x, y));
        } else {
            if (cells[x][y].m_piece->get_player_type() != owner) {
                pos.push_back(Position(x, y));
            }
            break;
        }
    }

    // Направо вверх
    for (int x = start.x + 1, y = start.y - 1; x <= 7 && y >= 0; ++x, --y) {
        if (cells[x][y].m_piece == nullptr) {
            pos.push_back(Position(x, y));
        } else {
            if (cells[x][y].m_piece->get_player_type() != owner) {
                pos.push_back(Position(x, y));
            }
            break;
        }
    }

    // Направо вниз
    for (int x = start.x + 1, y = start.y + 1; x <= 7 && y <= 7; ++x, ++y) {
        if (cells[x][y].m_piece == nullptr) {
            pos.push_back(Position(x, y));
        } else {
            if (cells[x][y].m_piece->get_player_type() != owner) {
                pos.push_back(Position(x, y));
            }
            break;
        }
    }
}

bool Piece::IfPosCorrect(Position pos)
{
    if (pos.x >= 0 && pos.x <= 7 && pos.y >= 0 && pos.y <=7) return true;
    return false;
}


