#ifndef ACTIONS_H
#define ACTIONS_H

#include <memory>
#include <QVector2D>
#include "weapon.h"

class Actions {
    public:
        bool moveRight = false;
        bool moveLeft = false;
        bool jump = false;
        bool shoot = false;

        double damaged = 0;
        int damagedCooldown = 0;
        QVector2D damageDirection;

        std::shared_ptr<Weapon> weapon = nullptr;

        Actions();

        void reset();
};

#endif // ACTIONS_H
