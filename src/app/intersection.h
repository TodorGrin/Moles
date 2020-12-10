#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <QPointF>

struct Intersection {
        enum class Type {
            NoIntersection,
            UnboundedIntersection,
            BoundedIntersection
        };

        Type type = Type::NoIntersection;
        QPointF point;
};

#endif // INTERSECTION_H
