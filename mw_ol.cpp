#include "mw_ol.h"
#include "ui_mw_ol.h"

mw_ol::mw_ol(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mw_ol)
{
    ui->setupUi(this);
    //
    ovcl = new QList<OpenVPNCLIENT*> ();
    dS   = new dSettings;
    sw   = new statusWidget;
    connect(dS, SIGNAL(_updateSettings(int, QString)), this, SLOT(updateSettings(int, QString)));
    //
    freq = 2000;
    //
    timer = new QTimer(this);
    startUpdate();
    connect(timer, SIGNAL(timeout()), this, SLOT(updateList()));
    updateList();
    //
    setupMenu();
}

mw_ol::~mw_ol()
{
    delete ui;
}

void mw_ol::on_ping(){
    ;//
#ifdef WIN32
    // TODO
#elif defined (W_OS_LINUX)

#endif
}

void mw_ol::on_RemoteDesktop(){
    ;//
#ifdef WIN32
    // TODO
#elif defined (W_OS_LINUX)

#endif
}

void mw_ol::showItemMenu(const QPoint &pos){
    //
    itemMenu->clear();
    //
    itemMenu->addAction(QString("PING"), this,SLOT(on_ping()));
    itemMenu->addAction(QString("Remote Desktop"), this,SLOT(on_RemoteDesktop()));
    //
    itemMenu->popup(ui->treeWidget->viewport()->mapToGlobal(pos));
}

void mw_ol::setupMenu(){
    //
    ui->treeWidget->setColumnCount(3);
    ui->treeWidget->setHeaderLabels(QStringList() << "Common name" << "Virtual Address" << "Real Address");
    //
    ui->treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    itemMenu = new QMenu(this);
    connect(ui->treeWidget, SIGNAL(customContextMenuRequested(QPoint)),
                this, SLOT(showItemMenu(QPoint)));
    //
    ui->statusBar->addWidget(sw);
    connect(ui->actSettings, SIGNAL(triggered()), this, SLOT(setupDialog()));
    connect(ui->actStart,    SIGNAL(triggered()), this, SLOT(startUpdate()));
    connect(ui->actStop,     SIGNAL(triggered()), this, SLOT(stopUpdate()));
    connect(ui->actExit,     SIGNAL(triggered()), this, SLOT(close()));
}

void mw_ol::parseConfig(){
    //
    QString s = QString(fd->downloadedData());
    //
    QStringList sl = s.split("\n");
/*
OpenVPN CLIENT LIST
Updated,<Wed Mar 15 16:05:46 2017>
Common Name,Real Address,Bytes Received,Bytes Sent,Connected Since
pavelk-tk,193.232.68.38:54231,1171930333,5629838050,Mon Mar  6 14:31:49 2017
ROUTING TABLE
Virtual Address,Common Name,Real Address,Last Ref
172.16.1.10,<NAME>,<IP>:54231,Wed Mar 15 16:05:44 2017
GLOBAL STATS
Max bcast/mcast queue length,2
END
*/
    ovcl->clear();
    //
    bool readClients = false;
    for (int i=0;i<sl.count();i++){
        //
        QString line = QString(sl.at(i));
        QStringList slDetails = line.split(",");
        //
//        code = getCode(line);
        //
        QString fv = slDetails.at(0);
        //
        if (QString::compare(fv, "Updated", Qt::CaseInsensitive) == 0) {
            sw->updateInfo(slDetails.at(1));
        }
        if (QString::compare(fv, "GLOBAL STATS", Qt::CaseInsensitive) == 0) {
            readClients = false;
        }
        //
        if (readClients) {
            OpenVPNCLIENT *ovc = new OpenVPNCLIENT;
            ovc->VirtualAddress = slDetails.at(0);
            ovc->CommonName     = slDetails.at(1);
            ovc->RealAddress    = slDetails.at(2);
            ovc->LastRef        = slDetails.at(3);
            //
            ovcl->append(ovc);
        }
        //
        if (QString::compare(fv, "Virtual Address", Qt::CaseInsensitive) == 0) {
            readClients = true;
        }
        //
    }
    showClients();

}

void mw_ol::updateList(){
    //
    fd = new filedownloader(QUrl("http://172.16.1.1"));
    connect(fd, SIGNAL(downloaded()), SLOT(parseConfig()));
    connect(fd, SIGNAL(someError()), SLOT(_someError()));
}

int mw_ol::getCode(QString line){
    //
    if(line.compare("Common Name,Real Address,Bytes Received,Bytes Sent,Connected Since")){
        return 0;
    }
    if(line.compare("ROUTING TABLE")){
        return 1;
    }
    if(line.compare("Virtual Address,Common Name,Real Address,Last Ref")){
        return 3;
    }
    if(line.compare("GLOBAL STATS")){
        return 4;
    }
    return -1;
}
void mw_ol::showClients(){
    //
    ui->treeWidget->clear();

    QList<QTreeWidgetItem *> items;
    for(int i=0; i<ovcl->count(); i++)
    {
        items.append(new QTreeWidgetItem(ui->treeWidget,
                                     QStringList() <<
                                     ovcl->value(i)->CommonName <<
                                     ovcl->value(i)->VirtualAddress <<
                                     ovcl->value(i)->RealAddress
                                     ));
    }
    ui->treeWidget->addTopLevelItems(items);
    //
    fd->deleteLater();
}

void mw_ol::startUpdate(){
    //
    timer->start(freq);
}

void mw_ol::stopUpdate(){
    //
    timer->stop();
}
void mw_ol::setupDialog(){
    dS->show();
}

void mw_ol::updateSettings(int f, QString a){
    freq = f;
    address = a;
    stopUpdate();
    startUpdate();
}

void mw_ol::_someError(){
    ui->treeWidget->clear();
    //
    sw->updateInfo("No data now");
}
