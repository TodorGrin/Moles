#include "gameengine.h"

const float EPS = 1e-6;
const float G = 0.01;

GameEngine::GameEngine(const Terrain &terrain, int teamsCount) : terrain_(terrain), teamsCount_(teamsCount) {
    generate();
}

void GameEngine::generate() {
    std::vector<QColor> teamColors = {{244, 66, 54}, {156, 39, 176}, {33, 149, 243}, {76, 175, 79}};
    teams_.clear();
    terrain_.generate();

    for (int i = 0; i < teamsCount_; ++i) {
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
            if (c.actions().damagedCooldown > 0)
                c.actions().damagedCooldown--;

            if (c.actions().damageDirection.length() > EPS) {
                c.setSpeed(c.actions().damageDirection);
                c.actions().damageDirection = QVector2D(0, 0);
            }

            if (terrain_.tiles()[c.position().x()][c.position().y() + c.size().height() / 2 + EPS].isBackground())
                c.setSpeed(c.speed() + QVector2D(0, G));
            else if (!terrain_.tiles()[c.position().x()][c.position().y() + c.size().height() / 2].isBackground()) {
                c.setSpeed(QVector2D(c.speed().x() * 0.95, 0));
                c.setPosition(QVector2D(c.position().x(), floor(c.position().y() - c.size().height() / 2) + c.size().height() / 2));
            }
        }
    }

    Character &c = currentTeam().currentCharacter();
    if (c.actions().moveLeft && terrain_.tiles()[c.position().x() - c.size().width() / 2 - EPS][c.position().y()].isBackground())
        c.setPosition(c.position() + QVector2D(-c.stepLength(), 0));

    if (c.actions().moveRight && terrain_.tiles()[c.position().x() + c.size().width() / 2 + EPS][c.position().y()].isBackground())
        c.setPosition(c.position() + QVector2D(c.stepLength(), 0));

    if (c.actions().jump && !terrain_.tiles()[c.position().x()][c.position().y() + c.size().height() / 2 + EPS].isBackground())
        c.setSpeed(c.speed() + QVector2D(0, -25 * G));

    for (Team &team : teams_) {
        for (Character &c : team.characters()) {
            if (c.speed().x() < 0 && !terrain_.tiles()[c.position().x() - c.size().width() / 2 - EPS][c.position().y()].isBackground())
                c.setSpeed(QVector2D(0, c.speed().y()));

            if (c.speed().x() > 0 && !terrain_.tiles()[c.position().x() + c.size().width() / 2 + EPS][c.position().y()].isBackground())
                c.setSpeed(QVector2D(0, c.speed().y()));

            c.setPosition(c.position() + c.speed());
        }
    }

    if (c.actions().shoot) {
        c.actions().weapon->shoot(*this);
        nextTurn();
    }

    c.actions().reset();
}

void GameEngine::nextTurn() {
    for (int i = 1; i < teams_.size(); ++i) {
        int nextTeam = (currentTeam_ + i) % teams_.size();

        if (teams_[nextTeam].isAlive()) {
            teams_[nextTeam].nextTurn();
            currentTeam_ = nextTeam;
            return;
        }
    }
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
