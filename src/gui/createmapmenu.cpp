#include "createmapmenu.h"
#include "ui_createmapmenu.h"

CreateMapMenu::CreateMapMenu(QWidget *parent) : QWidget(parent), ui(new Ui::CreateMapMenu) {
    ui->setupUi(this);
}

CreateMapMenu::~CreateMapMenu() {
    delete ui;
}

void CreateMapMenu::on_backButton_clicked() {
    MainWindow::get(this)->openMainMenu();
}

void CreateMapMenu::on_okButton_clicked() {
    MainWindow::get(this)->openCreateTeamMenu();
}
