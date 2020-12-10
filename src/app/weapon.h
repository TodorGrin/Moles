#ifndef WEAPON_H
#define WEAPON_H

#include <memory>

class GameEngine;

class Weapon {
    public:
        double angle_ = 0;

        explicit Weapon();
        virtual ~Weapon() = default;

        virtual void shoot(GameEngine &engine) = 0;

        //virtual std::shared_ptr<Weapon> clone() = 0;
};

#endif // WEAPON_H
