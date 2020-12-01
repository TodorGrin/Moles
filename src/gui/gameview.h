#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QWidget>
#include <memory>
#include "terrain.h"

namespace Ui {
class GameView;
}

class GameView : public QWidget {
    Q_OBJECT

    public:
        explicit GameView(QWidget *parent = nullptr);
        ~GameView();

        void setTerrain(std::shared_ptr<Terrain> terrain);

    protected:
        void paintEvent(QPaintEvent *event) override;

    private:
        std::shared_ptr<Terrain> terrain_ = nullptr;

        Ui::GameView *ui;
};

#endif // GAMEVIEW_H
