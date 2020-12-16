#ifndef TERRAIN_H
#define TERRAIN_H

#include <QSize>
#include <vector>
#include "tile.h"

class Terrain {
    public:
        explicit Terrain(const QSize &size);

        std::vector<std::vector<Tile>>& tiles();
        QSize size() const;
        bool isInBounds(const QPointF &point) const;
        void generate();
        const Tile tile(const QPointF &point) const;

    private:
        QSize size_;
        std::vector<std::vector<Tile>> tiles_;
};

#endif // TERRAIN_H
