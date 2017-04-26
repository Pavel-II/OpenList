#include "dsettings.h"
#include "ui_dsettings.h"

dSettings::dSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dSettings)
{
    ui->setupUi(this);
}

dSettings::~dSettings()
{
    delete ui;
}

void dSettings::on_buttonBox_accepted()
{
    emit _updateSettings(ui->spinBox->value(),
                         ui->lE_address->text());
}
