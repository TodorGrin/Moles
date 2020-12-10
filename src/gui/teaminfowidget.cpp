#include "teaminfowidget.h"
#include "ui_teaminfowidget.h"
#include <QPalette>

TeamInfoWidget::TeamInfoWidget(Team &team, QWidget *parent) : QWidget(parent), ui(new Ui::TeamInfoWidget), team_(team) {
    ui->setupUi(this);

    ui->teamName->setText(team.name());
    ui->teamHealth->setStyleSheet(".QProgressBar::chunk{background-color: " + team.color().name() +"}");
}

TeamInfoWidget::~TeamInfoWidget() {
    delete ui;
}

void TeamInfoWidget::paintEvent(QPaintEvent *event) {
    setUpdatesEnabled(false);

    ui->teamHealth->setValue(100 * team_.health() / team_.maxHealth());
    setVisible(team_.isAlive());

    setUpdatesEnabled(true);
}

