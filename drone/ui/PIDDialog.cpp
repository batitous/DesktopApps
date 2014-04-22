#include "piddialog.h"
#include "ui_piddialog.h"

PidDialog::PidDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PidDialog)
{
    ui->setupUi(this);

    connect(ui->bSend, SIGNAL(clicked()), this, SLOT(bSendEvent()));

    connect(ui->bCalib, SIGNAL(clicked()), this, SLOT(bCalibEvent()));

    ui->rollKp->setValue(0.4);
    ui->rollRateKp->setValue(0.1);
}

PidDialog::~PidDialog()
{
    delete ui;
}

void PidDialog::bSendEvent()
{
    mCoeff[0] = (float)ui->rollKp->value();
    mCoeff[1] = (float)ui->rollKi->value();
    mCoeff[2] = (float)ui->rollKd->value();
    mCoeff[3] = (float)ui->rollRateKp->value();

    mCoeff[4] = (float)ui->pitchKp->value();
    mCoeff[5] = (float)ui->pitchKi->value();
    mCoeff[6] = (float)ui->pitchKd->value();
    mCoeff[7] = (float)ui->pitchRateKp->value();

    emit sendEvent(mCoeff, COEFF_SIZE *4);
}

void PidDialog::bCalibEvent()
{
    mCoeff[0] = (float)ui->anglePitch->value();
    mCoeff[1] = (float)ui->angleRoll->value();

    emit calibEvent(mCoeff, 2 * 4);
}
