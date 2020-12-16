#include "terrain.h"

Terrain::Terrain(const QSize &size) : size_(size), tiles_(size.width()) {

}

std::vector<std::vector<Tile>>& Terrain::tiles() {
    return tiles_;
}

QSize Terrain::size() const {
    return size_;
}

bool Terrain::isInBounds(const QPointF &point) const {
    return point.x() >= 0 && point.y() >= 0 && point.x() < size_.width() && point.y() < size_.height();
}

void Terrain::generate() {
    tiles_.clear();
    tiles_.resize(size_.width());
    std::vector<double> heights(size_.width());

    for (int i = 0; i < size_.width(); ++i) {
        heights[i] = (((double) rand()) / RAND_MAX) * size_.height();
    }

    for (int i = 0; i < 8; ++i) {
        for (int x = 1; x < size_.width() - 1; ++x) {
            heights[x] = (heights[x - 1] + heights[x] + heights[x + 1]) / 3;
        }
    }

    for (int x = 0; x < size_.width(); ++x) {
        for (int i = 0; i < size_.height() - heights[x]; ++i) {
            tiles_[x].emplace_back(QColor::fromRgb(128, 217, 255));
        }

        for (int i = 0; i < heights[x]; ++i) {
            tiles_[x].emplace_back(QColor::fromRgb(76, 175, 79), QColor::fromRgb(128, 217, 255));
        }
    }
}

const Tile Terrain::tile(const QPointF &point) const {
    if (isInBounds(point))
        return tiles_[point.x()][point.y()];

    return Tile(QColor::fromRgb(128, 217, 255));
}
