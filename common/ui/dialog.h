#ifndef DIALOG_H
#define DIALOG_H

#include <QtCore/QObject>
#include <QtWidgets/QDialog>
#include <QtCore/QPoint>
#include <QMouseEvent>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    enum Type
    {
        Information,
        Error,
        Warning,
        Success
    };

    enum Role
    {
        Accept,
        Reject,
        Hide
    };

    enum ButtonChoice
    {
        Left,
        Right
    };

    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

    void setButton(Dialog::ButtonChoice choice, Dialog::Role role, const QString & t, bool def);

    int show(Dialog::Type type, const QString & title, const QString & message);

protected:
    void mousePressEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * event);

private:
    Ui::Dialog *ui;

    QPoint      mOrigin;
    QPoint      mAnchor;
    bool        mMoveAllowed;

    static QPixmap * mInfos;
    static QPixmap * mTick;
    static QPixmap * mCross;
    static QPixmap * mWarn;
};

#endif // DIALOG_H
