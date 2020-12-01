#include "createteammenu.h"
#include "ui_createteammenu.h"

CreateTeamMenu::CreateTeamMenu(QWidget *parent) : QWidget(parent), ui(new Ui::CreateTeamMenu) {
    ui->setupUi(this);
}

CreateTeamMenu::~CreateTeamMenu() {
    delete ui;
}

void CreateTeamMenu::on_backButton_clicked() {
    MainWindow::get(this)->openCreateMapMenu();
}

void CreateTeamMenu::on_playButton_clicked() {
    MainWindow::get(this)->openGameView();
}
