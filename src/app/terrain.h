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

        static void addNoise(std::vector<double> &vec, int width, int minHeight, int maxHeight, int numPoints, double (*interp)(double t));
        static double smoothstep(double t);
};

#endif // TERRAIN_H
