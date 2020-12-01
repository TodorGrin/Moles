#ifndef CREATEMAPMENU_H
#define CREATEMAPMENU_H

#include <QWidget>
#include "mainwindow.h"
#include "terrain.h"

namespace Ui {
class CreateMapMenu;
}

class CreateMapMenu : public QWidget {
    Q_OBJECT

    public:
        explicit CreateMapMenu(QWidget *parent = nullptr);
        ~CreateMapMenu();

        void setGameEngine(std::shared_ptr<GameEngine> gameEngine);

    private slots:
        void on_backButton_clicked();

        void on_okButton_clicked();

private:
        MainWindow* main_window_;

        Ui::CreateMapMenu *ui;
};

#endif // CREATEMAPMENU_H
