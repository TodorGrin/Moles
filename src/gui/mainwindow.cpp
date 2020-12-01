#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "createmapmenu.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    engine_ = std::make_shared<GameEngine>(Terrain(QSize(200, 100)), 4);
}

MainWindow::~MainWindow() {
    delete ui;
}

MainWindow* MainWindow::get(QWidget *widget) {
    MainWindow *main_window = dynamic_cast<MainWindow*>(widget->window());

    if (main_window == nullptr)
        qFatal("Can't find MainWindow");

    return main_window;
}

void MainWindow::openMainMenu() {
    ui->createMapMenu->setGameEngine(nullptr);
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::openCreateMapMenu() {
    ui->createMapMenu->setGameEngine(engine_);
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::openCreateTeamMenu() {
    ui->createMapMenu->setGameEngine(nullptr);
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::openGameView() {
    ui->gameView->setGameEngine(engine_);
    ui->stackedWidget->setCurrentIndex(3);
}
