#include "team.h"


Team::Team(const QString &name, int charactersCount, const QColor &color) : name_(name), characters_(charactersCount), color_(color) {
}

void Team::nextTurn() {
    currentCharacter_ = (currentCharacter_ + 1) % characters_.size();
}

Character &Team::currentCharacter() {
    return characters_[currentCharacter_];
}

QColor Team::color() const {
    return color_;
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
