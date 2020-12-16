#include "gameoverdialog.h"
#include "ui_gameoverdialog.h"

GameOverDialog::GameOverDialog(const QString &teamWon, QWidget *parent) : QDialog(parent), ui(new Ui::GameOverDialog){
    ui->setupUi(this);

    ui->gameOverLabel->setText(teamWon + " has won!");

    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
}

GameOverDialog::~GameOverDialog() {
    delete ui;
}

void GameOverDialog::on_okButton_clicked() {
    close();
}
