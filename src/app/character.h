#ifndef CHARACTER_H
#define CHARACTER_H

#include <QVector2D>
#include <QSize>

class Character {
    public:
        Character();

        void setPosition(const QVector2D &position);
        void setSpeed(const QVector2D &speed);
        void damage(int damageAmount);

        QVector2D speed();
        int health() const;
        static int maxHealth();
        static QSizeF size();
        static float stepLength();
        QVector2D position() const;

    private:
        int health_ = maxHealth();
        QVector2D position_ = {0, 0};
        QVector2D speed_ = {0, 0};
};

#endif // CHARACTER_H
