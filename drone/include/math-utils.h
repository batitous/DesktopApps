#ifndef MATHUTILS_H
#define MATHUTILS_H

extern float mapInputToOutput(float x, float in_min, float in_max, float out_min, float out_max);

extern float joystickCurve(float input, float sensibility, float trim, float inputMin, float inputMax);



#endif // MATHUTILS_H
