#include "terrain.h"
#include "rand.h"

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

void Terrain::addNoise(std::vector<double> &vec, int width, int minHeight, int maxHeight, int numPoints, double (*interp)(double t)) {
    double prevX = 0;
    double prevHeight = Rand::doubleInRange(minHeight, maxHeight);
    double nextHeight = Rand::doubleInRange(minHeight, maxHeight);

    for (int i = 0; i < width; ++i) {
        if (i - prevX > width / numPoints) {
            prevX = i;
            prevHeight = nextHeight;
            nextHeight = Rand::doubleInRange(minHeight, maxHeight);
        }

        double scaleX = width / numPoints;
        double scaleY = nextHeight - prevHeight;

        vec[i] += interp((i - prevX) / scaleX) * scaleY + prevHeight;
    }
}

double Terrain::smoothstep(double t) {
    return 6 * pow(t, 5) - 15 * pow(t, 4) + 10 * pow(t, 3);
}

void Terrain::generate() {
    changed_ = true;
    tiles_.clear();
    tiles_.resize(size_.width());
    std::vector<double> heights(size_.width());

    addNoise(heights, size_.width(), size_.height() / 2, size_.height() * 3 / 4, 10, &Terrain::smoothstep);
    addNoise(heights, size_.width(), 0, size_.height() / 10, 20, &Terrain::smoothstep);
    addNoise(heights, size_.width(), 0, size_.height() / 20, 50, &Terrain::smoothstep);

    for (int x = 0; x < size_.width(); ++x) {
        for (int i = 0; i < size_.height() - heights[x]; ++i) {
            tiles_[x].emplace_back(QColor::fromRgb(128, 217, 255));
        }

        for (int i = 0; i < heights[x]; ++i) {
            tiles_[x].emplace_back(QColor::fromRgb(76, 175, 79), QColor::fromRgb(128, 217, 255));
        }
    }
}

void Terrain::setChanged(bool val) {
    changed_ = val;
}

bool Terrain::changed() const {
    return changed_;
}

const Tile Terrain::tile(const QPointF &point) const {
    if (isInBounds(point))
        return tiles_[point.x()][point.y()];

    return Tile(QColor::fromRgb(128, 217, 255));
}
