#include "terrain.h"

Terrain::Terrain(const QSize &size) : size_(size), tiles_(size.width()) {
    float slopeHeight = size.height() / 10;
    float skyHeight = size.height() / 2;

    for (int x = 0; x < size.width(); ++x) {
        for (int y = 0; y < size.height(); ++y) {
            if (y < skyHeight + slopeHeight * x / size.width())
                tiles_[x].emplace_back(QColor::fromRgb(128, 217, 255));
            else
                tiles_[x].emplace_back(QColor::fromRgb(76, 175, 79));
        }
    }
}

std::vector<std::vector<Tile>>& Terrain::tiles() {
    return tiles_;
}

QSize& Terrain::size() {
    return size_;
}
