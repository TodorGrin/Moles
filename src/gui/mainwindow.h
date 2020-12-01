#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "terrain.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

        void openMainMenu();
        void openCreateMapMenu();
        void openCreateTeamMenu();
        void openGameView();

        static MainWindow* get(QWidget *widget);

    private:
        std::shared_ptr<Terrain> terrain_;

        Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
