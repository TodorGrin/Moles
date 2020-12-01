#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include "mainwindow.h"

namespace Ui {
class MainMenu;
}

class MainMenu : public QWidget {
    Q_OBJECT

    public:
        explicit MainMenu(QWidget *parent = nullptr);
        ~MainMenu();

    private slots:
        void on_playButton_clicked();

    private:
        MainWindow *main_window_;

        Ui::MainMenu *ui;
};

#endif // MAINMENU_H
