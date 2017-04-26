#include "statuswidget.h"
#include "ui_statuswidget.h"

statusWidget::statusWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::statusWidget)
{
    ui->setupUi(this);
}

statusWidget::~statusWidget()
{
    delete ui;
}

void statusWidget::updateInfo(QString time){
    ui->lUpdateTime->setText(time);
}
