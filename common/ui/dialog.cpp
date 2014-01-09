#include "dialog.h"
#include "ui_dialog.h"

#include "../include/desktopapp.h"

QPixmap * Dialog::mInfos = 0;
QPixmap * Dialog::mTick = 0;
QPixmap * Dialog::mCross = 0;
QPixmap * Dialog::mWarn = 0;

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    if ( mInfos == 0)
    {
        mInfos = new QPixmap(Utils::getAppDirPath() + "/resources/dialog/infos.png");
        mTick = new QPixmap(Utils::getAppDirPath() + "/resources/dialog/tick.png");
        mCross = new QPixmap(Utils::getAppDirPath() + "/resources/dialog/cross.png");
        mWarn = new QPixmap(Utils::getAppDirPath() + "/resources/dialog/warn.png");
    }

    this->setWindowModality(Qt::ApplicationModal);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Window);
    this->setStyleSheet("color: #000000; font-family: Arial; font-size: 14px;");

    ui->title->setStyleSheet("QLabel { font-weight: bold; font-family: Arial; font-size: 16px; }");
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::setButton(ButtonChoice choice, Dialog::Role role, const QString & t, bool def)
{
    QPushButton * button = ui->left;
    if (choice == Dialog::Right)
    {
        button = ui->right;
    }

    if (role == Dialog::Hide)
    {
        button->hide();
        return;
    }

    button->show();

    if (role == Dialog::Accept)
    {
        connect(button, SIGNAL(clicked()), this, SLOT(accept()));
    }

    if (role == Dialog::Reject)
    {
        connect(button, SIGNAL(clicked()), this, SLOT(reject()));
    }

    button->setText(t);

    this->setFocus();
    button->setDefault(def);
}

int Dialog::show(Dialog::Type type, const QString & title, const QString & message)
{
    if (type == Dialog::Information)
        ui->pixmap->setPixmap(*mInfos);
    if (type == Dialog::Success)
        ui->pixmap->setPixmap(*mTick);
    if (type == Dialog::Error)
        ui->pixmap->setPixmap(*mCross);
    if (type == Dialog::Warning)
        ui->pixmap->setPixmap(*mWarn);

    ui->title->setText(title);
    ui->title->setWordWrap(true);

    ui->message->setText(message);
    ui->message->setWordWrap(true);

    return this->exec();
}

void Dialog::mousePressEvent(QMouseEvent * event)
{
    if (event->button() != Qt::LeftButton)
        return;

    mAnchor = event->globalPos();
    mOrigin = this->pos();

    QRect r(this->pos(), QPoint(this->pos().x() + this->width(), this->pos().y() + 40));
    if (r.intersects(QRect(mAnchor, mAnchor)))
    {
        mMoveAllowed = true;
    }
}

void Dialog::mouseMoveEvent(QMouseEvent * event)
{
    if (event->buttons() != Qt::LeftButton)
        return;

    if (!mMoveAllowed)
        return;

    QPoint m = event->globalPos() - mAnchor;
    QPoint p = mOrigin + m;

    if (p.x() < 0)
        p.setX(0);
    if (p.y() < 0)
        p.setY(0);

    this->move(p);
}

void Dialog::mouseReleaseEvent(QMouseEvent * event)
{
    Q_UNUSED(event);

    mMoveAllowed = false;
}
