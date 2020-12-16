#include "bazooka.h"
#include "gameengine.h"
#include <QVector2D>

Bazooka::Bazooka() : Gun(0.01, 1, 45, 0.25, 1) {

}

QString Bazooka::name() const {
    return "Bazooka";
}

void Bazooka::onTileHit(const QPointF &position, GameEngine &engine) {
    for (int x = position.x() - explosionRadius_; x <= position.x() + explosionRadius_; ++x) {
        for (int y = position.y() - explosionRadius_; y <= position.y() + explosionRadius_; ++y) {
            QPointF point(x, y);

            if (QVector2D(point - position).length() > explosionRadius_)
                continue;

            if (!engine.terrain().isInBounds(point))
                continue;

            engine.terrain().tiles()[x][y].destroy();
        }
    }

    for (auto team : engine.teams()) {
        for (Character &ch : team->characters()) {
            double distanceToExplosionCenter = (ch.position() - QVector2D(position)).length();

            if (distanceToExplosionCenter <= explosionRadius_) {
                ch.damage(45 * (1 - distanceToExplosionCenter / (2 * explosionRadius_)));
            }
        }
    }
}

