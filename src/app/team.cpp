#include "team.h"


Team::Team(const QString &name, int charactersCount, const QColor &color) : name_(name), characters_(charactersCount), color_(color) {
}

void Team::nextTurn() {
    for (int i = 1; i <= characters_.size(); ++i) {
        int nextCharacter = (currentCharacter_ + i) % characters_.size();

        if (characters_[nextCharacter].isAlive()) {
            currentCharacter_ = nextCharacter;
            return;
        }
    }
}

Character &Team::currentCharacter() {
    return characters_[currentCharacter_];
}

bool Team::isAlive() const {
    for (auto &ch : characters_)
        if (ch.isAlive())
            return true;

    return false;
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
