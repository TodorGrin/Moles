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
    float width = painter.window().width();
    float height = painter.window().height();
    int tileSize = std::min(width / terrain_->size().width(), height / terrain_->size().height());
    QPoint shift((width - terrain_->size().width() * tileSize) / 2, height - terrain_->size().height() * tileSize);

    painter.fillRect(0, 0, painter.window().width(), painter.window().height(), QColor::fromRgb(128, 217, 255));
    painter.translate(shift);
    for (int x = 0; x < terrain_->size().width(); ++x) {
        for (int y = 0; y < terrain_->size().height(); ++y) {
            QRect rec(QPoint(x, y) * tileSize, QSize(tileSize, tileSize));
            painter.fillRect(rec, terrain_->tiles()[x][y].color());
        }
    }
}
