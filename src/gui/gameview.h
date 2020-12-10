#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QWidget>
#include <memory>
#include <QTimer>
#include <QMouseEvent>
#include "gameengine.h"

namespace Ui {
class GameView;
}

class GameView : public QWidget {
    Q_OBJECT

    public:
        explicit GameView(QWidget *parent = nullptr);
        ~GameView();

        void setGameEngine(std::shared_ptr<GameEngine> gameEngine);
        std::shared_ptr<GameEngine> gameEngine();

    protected:
        void paintEvent(QPaintEvent *event) override;
        void keyPressEvent(QKeyEvent *event) override;
        void keyReleaseEvent(QKeyEvent *event) override;
        void mouseMoveEvent(QMouseEvent *event) override;

    private:
        std::shared_ptr<GameEngine> engine_ = nullptr;
        QTimer *tickTimer_;
        QSizeF size_;
        Ui::GameView *ui;

        void drawTeamsInfo(QPainter &painter);
        void drawCharacters(QPainter &painter, int tileSize);
        void drawTerrain(QPainter &painter);

    private slots:
        void nextTick();
        void on_pushButton_clicked();
};

#endif // GAMEVIEW_H
