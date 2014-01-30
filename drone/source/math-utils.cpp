// Baptiste Burles, Kliplab, 2014

#include <math.h>


float mapInputToOutput(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


float joystickCurve(float input, float sensibility, float trim, float inputMin, float inputMax)
{
    float output;

    output = pow(input, sensibility);

    return mapInputToOutput(output, pow(inputMin,sensibility), pow(inputMax,sensibility), -1.0, 1.0) + trim;
}

