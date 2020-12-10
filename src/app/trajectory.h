#ifndef PARABOLA_H
#define PARABOLA_H

#include <QVector2D>
#include <QLineF>
#include <QSize>
#include "intersection.h"

class Trajectory {
    public:
        Trajectory(const QVector2D &start, const QVector2D &speed, double g);
        std::pair<Intersection, Intersection> intersects(const QLineF &line);

        bool nextPoint(const QSize &terrainSize, QPointF &nextPoint);

        QVector2D start();
        QPointF point(double t);
        double t(const QPointF &point);

    private:
        double a_, b_, c_;

        QVector2D start_, speed_;

        bool isInBounds(const QLineF& line, const QPointF &point);
};

#endif // PARABOLA_H
