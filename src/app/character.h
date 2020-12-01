#ifndef CHARACTER_H
#define CHARACTER_H


class Character {
    public:
        Character();

        void damage(int damageAmount);

        int health() const;
        static int maxHealth();

    private:
        int health_;
};

#endif // CHARACTER_H
