#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gameengine.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

        void openMainMenu();
        void openCreateTeamMenu();
        void openCreateMapMenu(std::shared_ptr<GameEngine> engine_);
        void openGameView(std::shared_ptr<GameEngine> engine_);

        static MainWindow* get(QWidget *widget);

    private:
        std::shared_ptr<GameEngine> engine_;

        Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
