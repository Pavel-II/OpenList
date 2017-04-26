#ifndef MW_OL_H
#define MW_OL_H

#include <QMainWindow>
#include <QLabel>
#include <QList>
#include <QTimer>
#include <QAction>
#include <QMessageBox>
#include <QMenu>
#include <QPoint>
#include <QProcess>
//
#include <filedownloader.h>
#include <openvpnclient.h>
#include <dsettings.h>
#include <statuswidget.h>

namespace Ui {
class mw_ol;
}

class mw_ol : public QMainWindow
{
    Q_OBJECT

public:
    explicit mw_ol(QWidget *parent = 0);
    ~mw_ol();

private:
    Ui::mw_ol *ui;
    filedownloader *fd;
    //
    int freq;
    QString address;
    //
    void setupMenu();
    int getCode(QString line);
    void showClients();
    //
    QList<OpenVPNCLIENT*> *ovcl;
    //
    QTimer *timer;
    dSettings *dS;
    statusWidget *sw;
    QMenu *itemMenu;

private slots:
    void parseConfig();
    void _someError();
    void updateList();
    void updateSettings(int f, QString a);
    void startUpdate();
    void stopUpdate();
    void setupDialog();
    //
    void showItemMenu(const QPoint &pos);
    void on_ping();
    void on_RemoteDesktop();
};

#endif // MW_OL_H
