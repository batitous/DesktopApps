// Baptiste Burles, Kliplab, 2014

#include "../include/joystick.h"

#include <QtCore/QDebug>


Joystick* Joystick::joystick = 0;


Joystick::Joystick(uint32_t idx)
{
    mIndex = idx;

    unsigned int buttons = sf::Joystick::getButtonCount(mIndex);

    bool hasX = sf::Joystick::hasAxis(mIndex, sf::Joystick::X);
    bool hasY = sf::Joystick::hasAxis(mIndex, sf::Joystick::Y);
    bool hasZ = sf::Joystick::hasAxis(mIndex, sf::Joystick::Z);

    qDebug() << "Joystick " << mIndex << "has:";
    qDebug() << "==>" << buttons << "buttons";
    qDebug() << "==> axis X" << hasX << "Y" << hasY << "Z" << hasZ;
    qDebug() << "==> axis R" << sf::Joystick::hasAxis(mIndex, sf::Joystick::R)
             << "U" << sf::Joystick::hasAxis(mIndex, sf::Joystick::U)
             << "V" << sf::Joystick::hasAxis(mIndex, sf::Joystick::V);

    // Joystick Chris
    mX = sf::Joystick::X;
    mY = sf::Joystick::Y;
    mZ = sf::Joystick::R;
}

Joystick::~Joystick()
{

}

void Joystick::update()
{
    sf::Joystick::update();

    mValues.x = sf::Joystick::getAxisPosition(mIndex, mX);
    mValues.y = sf::Joystick::getAxisPosition(mIndex, mY);
    mValues.z = sf::Joystick::getAxisPosition(mIndex, mZ);

    //isButtonPressed
}

const Point3d & Joystick::values()
{
    return mValues;
}

Joystick* Joystick::instance()
{
    if (joystick==0)
    {
        sf::Joystick::update();

        for (int i=0 ; i < sf::Joystick::Count ; i++)
        {
            if (sf::Joystick::isConnected(i))
            {
                qDebug() << "Joystick " << i << " connected";

                joystick = new Joystick(i);
                break;
            }
        }

        if (joystick==0)
        {
            qDebug() << "Joystick::instance failed to detect joystick !";
        }
    }

    return joystick;
}
