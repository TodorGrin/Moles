#ifndef CHARACTER_H
#define CHARACTER_H

#include <QVector2D>
#include <QSize>

class Character {
    public:
        Character();

        void setPosition(const QVector2D &position);
        void damage(int damageAmount);

        int health() const;
        static int maxHealth();
        QVector2D position() const;
        static QSizeF size();

    private:
        int health_ = maxHealth();
        QVector2D position_ = {0, 0};
};

#endif // CHARACTER_H
