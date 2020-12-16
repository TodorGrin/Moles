#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "team.h"
#include "terrain.h"
#include <memory>
#include <vector>

class GameEngine {
    public:
        GameEngine(const Terrain &terrain, int teamsCount);

        void tick();
        void nextTurn();
        void generate();

        std::shared_ptr<Team> currentTeam();
        Terrain& terrain();
        std::vector<std::shared_ptr<Team>>& teams();

    private:
        Terrain terrain_;
        std::vector<std::shared_ptr<Team>> teams_;

        int teamsCount_;
        int currentTeam_ = 0;
};

#endif // GAMEENGINE_H
