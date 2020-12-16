#include "chooseweapondialog.h"
#include "ui_chooseweapondialog.h"

ChooseWeaponDialog::ChooseWeaponDialog(GameEngine &engine, QWidget *parent) : QDialog(parent), ui(new Ui::ChooseWeaponDialog), engine_(engine) {
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    ui->weaponsList->clear();

    for (auto &weapon : weapons_) {
        ui->weaponsList->addItem(weapon->name());
    }
}

ChooseWeaponDialog::~ChooseWeaponDialog() {
    delete ui;
}

void ChooseWeaponDialog::on_weaponsList_itemClicked(QListWidgetItem *item) {
    for (auto &weapon : weapons_) {
        if (weapon->name() == item->text()) {
            engine_.currentTeam()->currentCharacter().actions().weapon = weapon;
            close();
            return;
        }
    }
}
