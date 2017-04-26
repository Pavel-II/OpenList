#ifndef STATUSWIDGET_H
#define STATUSWIDGET_H

#include <QWidget>

namespace Ui {
class statusWidget;
}

class statusWidget : public QWidget
{
    Q_OBJECT

public:
    explicit statusWidget(QWidget *parent = 0);
    ~statusWidget();
    void updateInfo(QString time);

private:
    Ui::statusWidget *ui;
};

#endif // STATUSWIDGET_H
