#include "trajectory.h"

double EPS = 1e-6;

Trajectory::Trajectory(const QVector2D &start, const QVector2D &speed, double g) {
    start_ = start;
    speed_ = speed;

    a_ = g / (2 * speed.x() * speed.x());
    b_ = speed.y() / speed.x() - g * start.x() / (speed.x() * speed.x());
    c_ = start.y() - speed.y() * start.x() / speed.x() + g * start.x() * start.x() / (2 * speed.x() * speed.x());
}

std::pair<Intersection, Intersection> Trajectory::intersects(const QLineF &line) {
    double A, B, C;

    if (abs(line.x1() - line.x2()) < EPS) {
        A = 1;
        B = 0;
        C = -line.x1();
    }
    else {
        A = (line.y2() - line.y1()) / (line.x1() - line.x2());
        B = 1;
        C = -A * line.x1() - line.y1();
    }

    double eqA = B * a_;
    double eqB = A + B * b_;
    double eqC = B * c_ + C;

    double DD = eqB * eqB - 4 * eqA * eqC;

    if (DD < 0) {
        return std::make_pair<>(Intersection(), Intersection());
    }
    else if (abs(eqA) < EPS) {
        double x = -eqC / eqB;
        double y = a_ * x * x + b_ * x + c_;

        QPointF p(x, y);

        Intersection i = {isInBounds(line, p) ? Intersection::Type::BoundedIntersection : Intersection::Type::UnboundedIntersection, p};

        return std::make_pair<>(i, Intersection());
    }
    else {
        double x1 = (-eqB - sqrt(DD)) / (2 * eqA);
        double x2 = (-eqB + sqrt(DD)) / (2 * eqA);

        double y1 = a_ * x1 * x1 + b_ * x1 + c_;
        double y2 = a_ * x2 * x2 + b_ * x2 + c_;

        QPointF p1(x1, y1);
        QPointF p2(x2, y2);

        Intersection i1 = {isInBounds(line, p1) ? Intersection::Type::BoundedIntersection : Intersection::Type::UnboundedIntersection, p1};
        Intersection i2 = {isInBounds(line, p2) ? Intersection::Type::BoundedIntersection : Intersection::Type::UnboundedIntersection, p2};

        return std::make_pair<>(i1, i2);
    }
}

bool Trajectory::nextPoint(const QSize &terrainSize, QPointF &nextPoint) {
    QPoint p(nextPoint.x(), nextPoint.y());

    std::vector<QLineF> lines = {
        {p, p + QPoint(0, 1)},
        {p + QPoint(1, 0), p + QPoint(1, 1)},
        {p, p + QPoint(1, 0)},
        {p + QPoint(0, 1), p + QPoint(1, 1)}
    };

    std::vector<QPointF> intersections;

    for (QLineF &line : lines) {
        auto intr = intersects(line);

        if (intr.first.type == Intersection::Type::BoundedIntersection)
            intersections.push_back(intr.first.point);

        if (intr.second.type == Intersection::Type::BoundedIntersection)
            intersections.push_back(intr.second.point);
    }

    QPointF furthestPoint(start_.toPointF());
    for (QPointF &intr : intersections) {
        if (t(intr) > t(furthestPoint)) {
            furthestPoint = intr;
        }
    }

    nextPoint = point(t(furthestPoint) + 1e-4);

    return !(intersections.empty() || nextPoint.x() < 0 || nextPoint.y() < 0 || nextPoint.x() >= terrainSize.width() || nextPoint.y() >= terrainSize.height());
}

QVector2D Trajectory::start() {
    return start_;
}

QPointF Trajectory::point(double t) {
    double x;

    if (speed_.x() > 0)
        x = start_.x() + t;
    else
        x = start_.x() - t;

    return QPointF(x, a_ * x * x + b_ * x + c_);
}

double Trajectory::t(const QPointF &point) {
    return abs(point.x() - start_.x());
}

bool Trajectory::isInBounds(const QLineF& line, const QPointF &point) {
    QVector2D dv(point - start_.toPointF());

    if (dv.x() * speed_.x() < 0)
        return false;

    if (point.x() + EPS < std::min(line.x1(), line.x2()) || point.y() + EPS < std::min(line.y1(), line.y2()))
        return false;

    if (point.x() - EPS > std::max(line.x1(), line.x2()) || point.y() - EPS > std::max(line.y1(), line.y2()))
        return false;

    return true;
}
