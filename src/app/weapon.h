#ifndef WEAPON_H
#define WEAPON_H

#include <memory>
#include <QString>

class GameEngine;

class Weapon {
    public:
        double angle_ = 0;

        explicit Weapon();
        virtual ~Weapon() = default;

        virtual void shoot(GameEngine &engine) = 0;

        virtual QString name() const = 0;
};

#endif // WEAPON_H
