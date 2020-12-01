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

    private:
        QSize size_;
        std::vector<std::vector<Tile>> tiles_;
};

#endif // TERRAIN_H
