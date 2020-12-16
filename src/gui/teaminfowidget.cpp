#include "teaminfowidget.h"
#include "ui_teaminfowidget.h"
#include <QPalette>

TeamInfoWidget::TeamInfoWidget(std::weak_ptr<Team> team, QWidget *parent) : QWidget(parent), ui(new Ui::TeamInfoWidget), team_(team) {
    ui->setupUi(this);

    if (!team_.expired()) {
        auto team = team_.lock();

        ui->teamName->setText(team->name());
        ui->teamHealth->setStyleSheet(".QProgressBar::chunk{background-color: " + team->color().name() +"}");
    }
}

TeamInfoWidget::~TeamInfoWidget() {
    delete ui;
}

void TeamInfoWidget::paintEvent(QPaintEvent *event) {
    setUpdatesEnabled(false);

    if (!team_.expired()) {
        auto team = team_.lock();

        ui->teamHealth->setValue(100 * team->health() / team->maxHealth());
        setVisible(team->isAlive());
    }

    setUpdatesEnabled(true);
}

