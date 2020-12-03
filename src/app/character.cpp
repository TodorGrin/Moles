#include "character.h"
#include <algorithm>

Character::Character() : health_(maxHealth()) {

}

void Character::setPosition(const QVector2D &position) {
    position_ = position;
}

void Character::damage(int damageAmount) {
    health_ -= damageAmount;
    health_ = std::max(health_, 0);
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
