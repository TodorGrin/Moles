#ifndef CHOOSEWEAPONDIALOG_H
#define CHOOSEWEAPONDIALOG_H

#include <QDialog>
#include <QListWidget>
#include "weapons/bazooka.h"
#include "weapons/uzi.h"
#include "gameengine.h"

namespace Ui {
class ChooseWeaponDialog;
}

class ChooseWeaponDialog : public QDialog {
    Q_OBJECT

    public:
        explicit ChooseWeaponDialog(GameEngine &engine, QWidget *parent = nullptr);
        ~ChooseWeaponDialog();

    private:
        Ui::ChooseWeaponDialog *ui;
        GameEngine &engine_;

        std::vector<std::shared_ptr<Weapon>> weapons_ = {
            std::make_shared<Uzi>(),
            std::make_shared<Bazooka>()
        };

    private slots:
        void on_weaponsList_itemClicked(QListWidgetItem *item);
};

#endif // CHOOSEWEAPONDIALOG_H
