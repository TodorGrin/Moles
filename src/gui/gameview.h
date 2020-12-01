#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QWidget>
#include <memory>
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

    protected:
        void paintEvent(QPaintEvent *event) override;

    private:
        std::shared_ptr<GameEngine> engine_ = nullptr;
        Ui::GameView *ui;

        void drawTeamsInfo(QPainter &painter);
        void drawTerrain(QPainter &painter);
};

#endif // GAMEVIEW_H
