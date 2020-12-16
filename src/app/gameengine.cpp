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
        teams_.push_back(std::make_shared<Team>("Team " + QString::number(i + 1), 2, teamColors[i]));
        teams_[i]->characters()[0].damage((40 * i) % 100);

        for (Character &ch : teams_[i]->characters()) {
            float x = ((double) rand() / RAND_MAX) * terrain_.size().width();
            float y = ch.size().height() / 2;

            while (terrain_.tiles()[x][y].isBackground())
                ++y;

            ch.setPosition(QVector2D(x, y - 1));
        }
    }
}


void GameEngine::tick() {
    for (auto team : teams_) {
        for (Character &c : team->characters()) {
            if (c.actions().damagedCooldown > 0)
                c.actions().damagedCooldown--;

            if (c.actions().damageDirection.length() > EPS) {
                c.setSpeed(c.actions().damageDirection);
                c.actions().damageDirection = QVector2D(0, 0);
            }

            if (terrain_.isInBounds(c.position().toPointF())) {
                if (terrain_.tile(c.position().toPointF() + QPointF(0, c.size().height() / 2 + EPS)).isBackground())
                    c.setSpeed(c.speed() + QVector2D(0, G));
                else if (!terrain_.tile(c.position().toPointF() + QPointF(0, c.size().height() / 2)).isBackground()) {
                    c.setSpeed(QVector2D(c.speed().x() * 0.95, 0));
                    c.setPosition(QVector2D(c.position().x(), floor(c.position().y() - c.size().height() / 2) + c.size().height() / 2));
                }
            }
            else {
                c.setSpeed(c.speed() + QVector2D(0, G));
            }
        }
    }

    Character &c = currentTeam()->currentCharacter();

    if (!c.isAlive()) {
        nextTurn();
    }

    if (terrain_.isInBounds(c.position().toPointF())) {
        if (c.actions().moveLeft && terrain_.tile(c.position().toPointF() + QPointF(-c.size().width() / 2 - EPS, 0)).isBackground())
            c.setPosition(c.position() + QVector2D(-c.stepLength(), 0));

        if (c.actions().moveRight && terrain_.tile(c.position().toPointF() + QPointF(c.size().width() / 2 + EPS, 0)).isBackground())
            c.setPosition(c.position() + QVector2D(c.stepLength(), 0));

        if (c.actions().jump && !terrain_.tile(c.position().toPointF() + QPointF(0, c.size().height() / 2 + EPS)).isBackground())
            c.setSpeed(c.speed() + QVector2D(0, -25 * G));
    }

    for (auto team : teams_) {
        for (Character &c : team->characters()) {
            if (terrain_.isInBounds(c.position().toPointF())) {
                if (c.speed().x() < 0 && !terrain_.tile(c.position().toPointF() + QPointF(-c.size().width() / 2 - EPS, 0)).isBackground())
                    c.setSpeed(QVector2D(0, c.speed().y()));

                if (c.speed().x() > 0 && !terrain_.tile(c.position().toPointF() + QPointF(c.size().width() / 2 + EPS, 0)).isBackground())
                    c.setSpeed(QVector2D(0, c.speed().y()));
            }

            c.setPosition(c.position() + c.speed());

            if (c.position().y() > terrain_.size().height())
                c.damage(c.maxHealth());
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

        if (teams_[nextTeam]->isAlive()) {
            teams_[nextTeam]->nextTurn();
            currentTeam_ = nextTeam;
            return;
        }
    }
}

std::shared_ptr<Team> GameEngine::currentTeam() {
    return teams_[currentTeam_];
}

Terrain& GameEngine::terrain() {
    return terrain_;
}

std::vector<std::shared_ptr<Team>>& GameEngine::teams() {
    return teams_;
}
