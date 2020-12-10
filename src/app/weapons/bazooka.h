#ifndef BAZOOKA_H
#define BAZOOKA_H

#include "gun.h"

class Bazooka : public Gun {
    public:
        Bazooka();

        virtual QString name() const override;

    protected:
        const double explosionRadius_ = 5;

        virtual void onTileHit(const QPointF &position, GameEngine &engine) override;
};

#endif // BAZOOKA_H
