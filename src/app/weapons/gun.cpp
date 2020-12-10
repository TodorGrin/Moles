#include "gun.h"
#include "gameengine.h"
#include <QDebug>
#include <QLine>
#include <vector>
#include "trajectory.h"

Gun::Gun(double g, double power, double damage, double knockback, int maxTilesDestroyed) :
    g_(g),
    power_(power),
    damage_(damage),
    knockback_(knockback),
    maxTilesDestroyed_(maxTilesDestroyed)
{

}

void Gun::shoot(GameEngine &engine) {
    Terrain &t = engine.terrain();
    Character &curCh = engine.currentTeam().currentCharacter();
    QPointF chPos(curCh.position().toPointF());
    Trajectory ray(QVector2D(chPos), power_ * QVector2D(cos(angle_), sin(angle_)), g_);

    QPointF p(curCh.position().toPointF());
    QPointF prevP(p);
    int tilesDestroyed = 0;

    while (ray.nextPoint(t.size(), p)) {
        Tile &tile = t.tiles()[p.x()][p.y()];

        if (p == prevP) {
            qWarning() << "Error : two equal intersection points. Something is wrong with precision";
            break;
        }

        if (!tile.isBackground()) {
            tilesDestroyed++;

            if (tilesDestroyed >= maxTilesDestroyed_)
                break;
        }

        prevP = p;
        tile = Tile(QColor::fromRgb(128, 217, 255), true);
    }

    double reachLength = ray.t(p);
    for (Team &team : engine.teams()) {
        for (Character &ch : team.characters()) {
            if (&ch == &engine.currentTeam().currentCharacter() || ray.t(ch.position().toPointF()) > reachLength)
                continue;

            double x = ch.position().x();
            double y = ch.position().y();
            double sx = ch.size().width() / 2;
            double sy = ch.size().height() / 2;

            std::vector<QLineF> lines = {
                QLineF(x - sx, y - sy, x + sx, y - sy),
                QLineF(x - sx, y + sy, x + sx, y + sy),
                QLineF(x - sx, y - sy, x - sx, y + sy),
                QLineF(x + sx, y - sy, x + sx, y + sy)
            };

            bool hit = false;

            for (QLineF &line : lines) {
                auto i = ray.intersects(line);

                if (i.first.type == Intersection::Type::BoundedIntersection || i.second.type == Intersection::Type::BoundedIntersection) {
                    hit = true;
                    break;
                }
            }

            if (hit) {
                ch.damage(damage_);
                ch.actions().damaged = damage_;
                ch.actions().damageDirection = QVector2D(ch.position().toPointF() - ray.point(ray.t(ch.position().toPointF()) - 1)).normalized() * knockback_;
                ch.actions().damagedCooldown = 4 * 60;
            }
        }
    }
}
