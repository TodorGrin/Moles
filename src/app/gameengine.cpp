#include "gameengine.h"

const float EPS = 1e-6;
const float G = 0.05;

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

void GameEngine::tick() {
    for (Team &team : teams_) {
        for (Character &c : team.characters()) {
            c.setSpeed(QVector2D(0, 0));

            if (terrain_.tiles()[c.position().x()][c.position().y() + c.size().height() / 2 + EPS].isBackground())
                c.setSpeed(QVector2D(0, G));
            else if (!terrain_.tiles()[c.position().x()][c.position().y() + c.size().height() / 2].isBackground())
                c.setSpeed(QVector2D(0, -G));
        }
    }

    Character &c = currentTeam().currentCharacter();
    if (actions_.moveLeft) c.setSpeed(c.speed() + QVector2D(-c.stepLength(), 0));
    if (actions_.moveRight) c.setSpeed(c.speed() + QVector2D(c.stepLength(), 0));
    if (actions_.jump && !terrain_.tiles()[c.position().x()][c.position().y() + c.size().height() / 2 + EPS].isBackground()) c.setSpeed(c.speed() + QVector2D(0, -50 * G));

    for (Team &team : teams_) {
        for (Character &c : team.characters()) {
            if (c.speed().x() < 0 && !terrain_.tiles()[c.position().x() - c.size().width() / 2 - EPS][c.position().y()].isBackground())
                c.setSpeed(QVector2D(0, c.speed().y()));

            if (c.speed().x() > 0 && !terrain_.tiles()[c.position().x() + c.size().width() / 2 + EPS][c.position().y()].isBackground())
                c.setSpeed(QVector2D(0, c.speed().y()));

            c.setPosition(c.position() + c.speed());
        }
    }

    actions_.reset();
}

void GameEngine::nextTurn() {
    currentTeam_ = (currentTeam_ + 1) % teams_.size();
    currentTeam().nextTurn();
}

Team& GameEngine::currentTeam() {
    return teams_[currentTeam_];
}

Terrain& GameEngine::terrain() {
    return terrain_;
}

std::vector<Team>& GameEngine::teams() {
    return teams_;
}

Actions& GameEngine::actions() {
    return actions_;
}
