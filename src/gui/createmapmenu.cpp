#include "createmapmenu.h"
#include "ui_createmapmenu.h"

CreateMapMenu::CreateMapMenu(QWidget *parent) : QWidget(parent), ui(new Ui::CreateMapMenu) {
    ui->setupUi(this);
}

CreateMapMenu::~CreateMapMenu() {
    delete ui;
}

void CreateMapMenu::setGameEngine(std::shared_ptr<GameEngine> gameEngine) {
    ui->gameView->setGameEngine(gameEngine);
}

void CreateMapMenu::on_backButton_clicked() {
    MainWindow::get(this)->openCreateTeamMenu();
}

void CreateMapMenu::on_okButton_clicked() {
    MainWindow::get(this)->openGameView(ui->gameView->gameEngine());
}

void CreateMapMenu::on_generateButton_clicked() {
    ui->gameView->gameEngine()->generate();
}
