#ifndef DSETTINGS_H
#define DSETTINGS_H

#include <QDialog>

namespace Ui {
class dSettings;
}

class dSettings : public QDialog
{
    Q_OBJECT

public:
    explicit dSettings(QWidget *parent = 0);
    ~dSettings();

signals:
    void _updateSettings(int f, QString a);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::dSettings *ui;
};

#endif // DSETTINGS_H
