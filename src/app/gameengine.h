#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "team.h"
#include "terrain.h"
#include "actions.h"
#include <memory>
#include <vector>

class GameEngine {
    public:
        GameEngine(const Terrain &terrain, int teamsCount);

        void tick();
        void nextTurn();

        Team& currentTeam();
        Terrain& terrain();
        std::vector<Team>& teams();
        Actions& actions();

    private:
        Terrain terrain_;
        std::vector<Team> teams_;
        Actions actions_;

        int currentTeam_ = 0;
};

#endif // GAMEENGINE_H
