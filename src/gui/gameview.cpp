#include "gameview.h"
#include "ui_gameview.h"
#include <QPainter>
#include <QBrush>
#include <QPainterPath>
#include <QKeyEvent>

void GameView::keyPressEvent(QKeyEvent *event) {
    if (!engine_)
        return;

    if (event->key() == Qt::Key_D) engine_->actions().moveRight = true;
    if (event->key() == Qt::Key_A) engine_->actions().moveLeft = true;
    if (event->key() == Qt::Key_Space) engine_->actions().jump = true;
}

void GameView::keyReleaseEvent(QKeyEvent *event) {
    if (!engine_)
        return;

    if (event->key() == Qt::Key_D) engine_->actions().moveRight = false;
    if (event->key() == Qt::Key_A) engine_->actions().moveLeft = false;
    if (event->key() == Qt::Key_Space) engine_->actions().jump = false;
}

GameView::GameView(QWidget *parent) : QWidget(parent), ui(new Ui::GameView) {
    ui->setupUi(this);

    setFocusPolicy(Qt::StrongFocus);
    tickTimer_ = new QTimer(this);
    connect(tickTimer_, SIGNAL(timeout()), this, SLOT(nextTick()));
}

GameView::~GameView() {
    delete ui;
}

void GameView::nextTick() {
    if (!engine_)
        return;

    engine_->tick();
    update();
}

void GameView::setGameEngine(std::shared_ptr<GameEngine> gameEngine) {
    engine_ = gameEngine;

    if (engine_) {
        tickTimer_->stop();
        tickTimer_->start(1.0 / 60);
    }
    else
        tickTimer_->stop();
}

std::shared_ptr<GameEngine> GameView::gameEngine() {
    return engine_;
}

void GameView::paintEvent(QPaintEvent *event) {
    if (!engine_)
        return;

    QPainter painter(this);
    drawTerrain(painter);
    drawTeamsInfo(painter);
}

void GameView::drawTeamsInfo(QPainter &painter) {
    float spacing = 25;
    QPoint start(20, painter.device()->height() - 20);

    painter.save();
    painter.translate(start);
    painter.fillRect(-12, 12, 104, -12 -spacing * engine_->teams().size(), QColor::fromRgb(245, 123, 0));
    painter.fillRect(-10, 10, 100, -8 -spacing * engine_->teams().size(), QColor::fromRgb(255, 193, 7));
    painter.setPen(QColor::fromRgb(93, 64, 55));

    QFont font("Verdana", 8);
    font.setBold(true);
    painter.setFont(font);

    std::vector<Team> teams = engine_->teams();
    sort(teams.begin(), teams.end(), [](const Team &t1, const Team &t2) { return (float) t1.health() / t1.maxHealth() < (float) t2.health() / t2.maxHealth();});

    for (int i = 0; i < teams.size(); ++i) {
        Team &team = teams[i];

        painter.drawText(0, -spacing * i - 5, team.name());
        painter.fillRect(0, -spacing * i, 80.0 * team.health() / team.maxHealth(), 5, team.color());
    }

    painter.restore();
    painter.setFont(font);
    painter.setPen(engine_->currentTeam().color());
    painter.drawText(painter.device()->width() / 2, 20, engine_->currentTeam().name());
}

void GameView::drawCharacters(QPainter &painter, int tileSize) {
    for (Team &team : engine_->teams()) {
        painter.setBrush(QBrush(team.color(), Qt::SolidPattern));

        for (Character &ch : team.characters()) {
            painter.drawRect((ch.position().x() - ch.size().width() / 2) * tileSize,
                             (ch.position().y() - ch.size().height() / 2) * tileSize,
                             ch.size().width() * tileSize,
                             ch.size().height() * tileSize);
        }
    }
}

void GameView::drawTerrain(QPainter &painter) {
    Terrain &terrain = engine_->terrain();
    float width = painter.window().width();
    float height = painter.window().height();
    int tileSize = std::min(width / terrain.size().width(), height / terrain.size().height());
    QPoint shift((width - terrain.size().width() * tileSize) / 2, height - terrain.size().height() * tileSize);

    painter.save();
    painter.fillRect(0, 0, painter.window().width(), painter.window().height(), QColor::fromRgb(128, 217, 255));
    painter.translate(shift);

    for (int x = 0; x < terrain.size().width(); ++x) {
        for (int y = 0; y < terrain.size().height(); ++y) {
            QRect rec(QPoint(x, y) * tileSize, QSize(tileSize, tileSize));
            painter.fillRect(rec, terrain.tiles()[x][y].color());
        }
    }

    drawCharacters(painter, tileSize);
    painter.restore();
}

void GameView::on_pushButton_clicked() {
    if (!engine_)
        return;

    engine_->nextTurn();
}
