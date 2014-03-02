#ifndef PIDDIALOG_H
#define PIDDIALOG_H

#include <QDialog>

namespace Ui {
class PidDialog;
}

class PidDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PidDialog(QWidget *parent = 0);
    ~PidDialog();

 signals:
    void sendEvent(float *coeff, int size);

private slots:
    void bSendEvent();

private:
    #define COEFF_SIZE 4

    float mCoeff[COEFF_SIZE];

    Ui::PidDialog *ui;
};

#endif // PIDDIALOG_H
