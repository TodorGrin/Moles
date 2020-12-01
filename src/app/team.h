#ifndef TEAM_H
#define TEAM_H

#include "character.h"
#include <vector>
#include <QString>

class Team {
    public:
        explicit Team(const QString &name, int charactersCount);

        int health() const;
        int maxHealth() const;
        QString name() const;
        std::vector<Character>& characters();

    private:
        QString name_;
        std::vector<Character> characters_;
};

#endif // TEAM_H
