#include "character.h"
#include <algorithm>

Character::Character() : health_(maxHealth()) {

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
