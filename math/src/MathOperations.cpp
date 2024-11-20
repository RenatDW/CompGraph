#include "../headers/MathOperations.h"

float MathOperations::calculate_reverse_square(const float number)
{
    long i;
    float x2, y;
    const float three_halfs = 1.5f;

    x2 = number * 0.5F;
    y = number;
    i = *(long *) &y;
    i = 0x5F375A86 - (i >> 1);
    y = *(float *) &i;
    y = y * (three_halfs - (x2 * y * y));
    y = y * (three_halfs - (x2 * y * y));
    return y;
}
