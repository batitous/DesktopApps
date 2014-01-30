#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <babcode.h>
#include <SFML/Window/Joystick.hpp>

#include "gl/point3d.h"

class Joystick
{
public:
    static Joystick* instance();

    ~Joystick();

    void update();

    const Point3d & values();

private:
    Joystick(UInt32 idx);

    sf::Joystick::Axis        mX;
    sf::Joystick::Axis        mY;
    sf::Joystick::Axis        mZ;

    Point3d     mValues;

    UInt32      mIndex;

    static Joystick* joystick;
};


#endif // JOYSTICK_H
