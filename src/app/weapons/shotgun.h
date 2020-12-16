#ifndef SHOTGUN_H
#define SHOTGUN_H

#include "gun.h"
#include <QtMath>

class Shotgun : public Gun {
    public:
        Shotgun();

        virtual void shoot(GameEngine &engine) override;

        virtual QString name() const override;

    protected:
        const double scattering_ = M_PI / 6;
};

#endif // SHOTGUN_H
