#include "createteammenu.h"
#include "ui_createteammenu.h"

CreateTeamMenu::CreateTeamMenu(QWidget *parent) : QWidget(parent), ui(new Ui::CreateTeamMenu) {
    ui->setupUi(this);
}

CreateTeamMenu::~CreateTeamMenu() {
    delete ui;
}

void CreateTeamMenu::on_backButton_clicked() {
    MainWindow::get(this)->openMainMenu();
}

void CreateTeamMenu::on_playButton_clicked() {
    std::shared_ptr<GameEngine> engine = std::make_shared<GameEngine>(Terrain(QSize(600, 300)), ui->teamsCount->value());

    MainWindow::get(this)->openCreateMapMenu(engine);
}
