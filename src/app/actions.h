#ifndef ACTIONS_H
#define ACTIONS_H


class Actions {
    public:
        bool moveRight = false;
        bool moveLeft = false;
        bool jump = false;

        Actions();

        void reset();
};

#endif // ACTIONS_H
