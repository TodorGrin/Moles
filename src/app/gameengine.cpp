#include "gameengine.h"


GameEngine::GameEngine(const Terrain &terrain, int teamsCount) : terrain_(terrain) {
    for (int i = 0; i < teamsCount; ++i) {
        teams_.emplace_back("Team " + QString::number(i + 1), 4);
        teams_[i].characters()[0].damage((40 * i) % 100);
    }
}

Terrain &GameEngine::terrain() {
    return terrain_;
}

std::vector<Team> &GameEngine::teams() {
    return teams_;
}
