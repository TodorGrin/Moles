#ifndef GUN_H
#define GUN_H

#include "weapon.h"

class Gun : public Weapon {
    public:
        explicit Gun(double g, double power, double damage, double knockback, int maxTilesDestroyed);
        virtual ~Gun() = default;

        virtual void shoot(GameEngine &engine) override;

    protected:
        const double g_;
        const double power_;
        const double damage_;
        const double knockback_;
        const int maxTilesDestroyed_;
};

#endif // GUN_H
