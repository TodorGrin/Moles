#ifndef TILE_H
#define TILE_H

#include <QColor>

class Tile {
    public:
        explicit Tile(const QColor &color);

        QColor color();

    private:
        QColor color_;
};

#endif // TILE_H
