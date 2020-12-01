#ifndef CREATETEAMMENU_H
#define CREATETEAMMENU_H

#include <QWidget>
#include "mainwindow.h"

namespace Ui {
class CreateTeamMenu;
}

class CreateTeamMenu : public QWidget {
    Q_OBJECT

    public:
        explicit CreateTeamMenu(QWidget *parent = nullptr);
        ~CreateTeamMenu();

private slots:
    void on_backButton_clicked();

    void on_playButton_clicked();

private:
        Ui::CreateTeamMenu *ui;
};

#endif // CREATETEAMMENU_H
