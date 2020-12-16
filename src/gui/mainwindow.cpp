#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "createmapmenu.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
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
    ui->gameView->setGameEngine(nullptr);
    ui->stackedWidget->setCurrentIndex(0);
    setWindowState(Qt::WindowMaximized);
}

void MainWindow::openCreateTeamMenu() {
    ui->createMapMenu->setGameEngine(nullptr);
    ui->gameView->setGameEngine(nullptr);
    ui->stackedWidget->setCurrentIndex(2);
    setWindowState(Qt::WindowMaximized);
}

void MainWindow::openCreateMapMenu(std::shared_ptr<GameEngine> engine_) {
    ui->createMapMenu->setGameEngine(engine_);
    ui->gameView->setGameEngine(nullptr);
    ui->stackedWidget->setCurrentIndex(1);
    setWindowState(Qt::WindowMaximized);
}

void MainWindow::openGameView(std::shared_ptr<GameEngine> engine_) {
    ui->createMapMenu->setGameEngine(nullptr);
    ui->gameView->setGameEngine(engine_);
    ui->stackedWidget->setCurrentIndex(3);
    setWindowState(Qt::WindowFullScreen);
}
