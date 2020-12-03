#ifndef TEAM_H
#define TEAM_H

#include "character.h"
#include <vector>
#include <QString>
#include <QColor>

class Team {
    public:
        explicit Team(const QString &name, int charactersCount, const QColor &color);

        QColor color() const;
        int health() const;
        int maxHealth() const;
        QString name() const;
        std::vector<Character>& characters();

    private:
        QString name_;
        std::vector<Character> characters_;
        QColor color_;
};

#endif // TEAM_H
