#ifndef TILE_H
#define TILE_H

#include <QColor>

class Tile {
    public:
        explicit Tile(const QColor &color, const QColor backgroundColor);
        explicit Tile(const QColor backgroundColor);

        void destroy();

        QColor color();
        bool isBackground();

    private:
        QColor color_;
        QColor backgroundColor_;
        bool isBackground_;
};

#endif // TILE_H
