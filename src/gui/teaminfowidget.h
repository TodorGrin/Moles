#ifndef TEAMINFOWIDGET_H
#define TEAMINFOWIDGET_H

#include <QWidget>
#include "team.h"

namespace Ui {
class TeamInfoWidget;
}

class TeamInfoWidget : public QWidget {
    Q_OBJECT

    public:
        explicit TeamInfoWidget(Team &team, QWidget *parent = nullptr);
        ~TeamInfoWidget();

    protected:
        void paintEvent(QPaintEvent *event) override;

    private:
        Ui::TeamInfoWidget *ui;
        Team &team_;
};

#endif // TEAMINFOWIDGET_H
