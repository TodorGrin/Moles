#ifndef GAMEOVERDIALOG_H
#define GAMEOVERDIALOG_H

#include <QDialog>

namespace Ui {
class GameOverDialog;
}

class GameOverDialog : public QDialog {
    Q_OBJECT

    public:
        explicit GameOverDialog(const QString &teamWon, QWidget *parent = nullptr);
        ~GameOverDialog();

private slots:
    void on_okButton_clicked();

private:
        Ui::GameOverDialog *ui;
};

#endif // GAMEOVERDIALOG_H
