#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets/QPushButton>

#include "../../../common/include/desktopapp.h"
#include "../../../common/include/desktopui.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void bConnectEvent(void);
    void bClearEvent(void);

private:
    ComPortWidget * wComport;
    QPushButton * bConnect;

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
