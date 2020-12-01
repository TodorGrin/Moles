#include "team.h"


Team::Team(const QString &name, int charactersCount) : name_(name), characters_(charactersCount) {
}

int Team::health() const {
    int health = 0;

    for (auto &character : characters_)
        health += character.health();

    return health;
}

int Team::maxHealth() const {
    return characters_.size() * Character::maxHealth();
}

QString Team::name() const {
    return name_;
}

std::vector<Character>& Team::characters() {
    return characters_;
}
