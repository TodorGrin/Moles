#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "team.h"
#include "terrain.h"
#include <memory>
#include <vector>

class GameEngine {
    public:
        GameEngine(const Terrain &terrain, int teamsCount);

        Terrain& terrain();
        std::vector<Team>& teams();

    private:
        Terrain terrain_;
        std::vector<Team> teams_;
};

#endif // GAMEENGINE_H
