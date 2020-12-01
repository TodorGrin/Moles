#include "gameview.h"
#include "ui_gameview.h"
#include <QPainter>
#include <QBrush>

GameView::GameView(QWidget *parent) : QWidget(parent), ui(new Ui::GameView) {
    ui->setupUi(this);
}

GameView::~GameView() {
    delete ui;
}

void GameView::setTerrain(std::shared_ptr<Terrain> terrain) {
    terrain_ = terrain;
}

void GameView::paintEvent(QPaintEvent *event) {
    if (!terrain_)
        return;

    QPainter painter(this);
    int tileSize = static_cast<float>(painter.window().width()) / terrain_->size().width();

    for (int x = 0; x < terrain_->size().width(); ++x) {
        for (int y = 0; y < terrain_->size().height(); ++y) {
            QRect rec(QPoint(x, y) * tileSize, QSize(tileSize, tileSize));
            painter.fillRect(rec, QBrush(terrain_->tiles()[x][y].color(), Qt::SolidPattern));
        }
    }
}
