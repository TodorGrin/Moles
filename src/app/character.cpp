#include "character.h"
#include <algorithm>

Character::Character() : health_(maxHealth()) {

}

void Character::setPosition(const QVector2D &position) {
    position_ = position;
}

void Character::setSpeed(const QVector2D &speed) {
    speed_ = speed;
}

void Character::damage(int damageAmount) {
    health_ -= damageAmount;
    health_ = std::max(health_, 0);

    actions_.damaged = damageAmount;
    actions_.damagedCooldown = 4 * 60;
}

Actions &Character::actions() {
    return actions_;
}

bool Character::isAlive() const {
    return health_ > 0;
}

QVector2D Character::speed() const {
    return speed_;
}

int Character::health() const {
    return health_;
}

int Character::maxHealth() {
    return 100;
}

QVector2D Character::position() const {
    return position_;
}

QSizeF Character::size() {
    return QSizeF(1, 1);
}

float Character::stepLength() {
    return 0.02;
}
