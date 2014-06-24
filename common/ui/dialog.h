/* The MIT License (MIT)
 
 Copyright (c) 2014 Baptiste Burles, Kliplab
 
 Permission is hereby granted, free of charge, to any person obtaining a copy of
 this software and associated documentation files (the "Software"), to deal in
 the Software without restriction, including without limitation the rights to
 use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 the Software, and to permit persons to whom the Software is furnished to do so,
 subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 
 */

// Thanks to Romain from Dviance.
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
