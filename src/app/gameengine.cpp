#include "gameengine.h"


GameEngine::GameEngine(const Terrain &terrain, int teamsCount) : terrain_(terrain) {
    std::vector<QColor> teamColors = {{244, 66, 54}, {156, 39, 176}, {33, 149, 243}, {76, 175, 79}};

    for (int i = 0; i < teamsCount; ++i) {
        teams_.emplace_back("Team " + QString::number(i + 1), 2, teamColors[i]);
        teams_[i].characters()[0].damage((40 * i) % 100);

        for (Character &ch : teams_[i].characters()) {
            float x = ((double) rand() / RAND_MAX) * terrain_.size().width();
            float y = ch.size().height() / 2;

            while (terrain_.tiles()[x][y].isBackground())
                ++y;

            ch.setPosition(QVector2D(x, y - 1));
        }
    }
}

Terrain &GameEngine::terrain() {
    return terrain_;
}

std::vector<Team> &GameEngine::teams() {
    return teams_;
}
