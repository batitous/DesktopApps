#include "piddialog.h"
#include "ui_piddialog.h"

PidDialog::PidDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PidDialog)
{
    ui->setupUi(this);

    connect(ui->bSend, SIGNAL(clicked()), this, SLOT(bSendEvent()));

    ui->rollRate->setValue(0.4);
    ui->rollRateKp->setValue(0.1);
}

PidDialog::~PidDialog()
{
    delete ui;
}

void PidDialog::bSendEvent()
{
    mCoeff[0] = (float)ui->rollRate->value();
    mCoeff[1] = (float)ui->rollKi->value();
    mCoeff[2] = (float)ui->rollKd->value();
    mCoeff[3] = (float)ui->rollRateKp->value();

    emit sendEvent(mCoeff, COEFF_SIZE *4);
}

