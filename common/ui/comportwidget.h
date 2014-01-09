#ifndef COMPORTWIDGET_H
#define COMPORTWIDGET_H

#include <QWidget>

namespace Ui {
class ComPortWidget;
}

class ComPortWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ComPortWidget(QWidget *parent = 0);
    ~ComPortWidget();

    void refreshPortComList();

private slots:
    void activatedEvent(int index);

private:
    Ui::ComPortWidget *ui;

    QStringList         mPortComList;
};

#endif // COMPORTWIDGET_H
