#include "mainmenu.h"
#include "ui_mainmenu.h"
#include "mainwindow.h"
#include <QtGlobal>
#include <QDebug>

MainMenu::MainMenu(QWidget *parent) : QWidget(parent), ui(new Ui::MainMenu) {
    ui->setupUi(this);
}

MainMenu::~MainMenu() {
    delete ui;
}

void MainMenu::on_playButton_clicked() {
    MainWindow::get(this)->openCreateTeamMenu();
}
