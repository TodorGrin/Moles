#ifndef TILE_H
#define TILE_H

#include <QColor>

class Tile {
    public:
        explicit Tile(const QColor &color, bool isBackground);

        QColor color();
        bool isBackground();

    private:
        QColor color_;
        bool isBackground_;
};

#endif // TILE_H
