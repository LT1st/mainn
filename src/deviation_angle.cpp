#include "deviation_angle.h"

double reasense_x_angle = 27.68, reasense_y_angle = 19.91;
int central[2] = {320 , 240};

double deviation_angle_x(double a, double b)
{
    double x = 2 * (a - central[0]) / reasense_x_angle;
    return x;
}

double deviation_angle_y(double a, double b)
{
    double y = 2 * (a - central[1]) / reasense_y_angle;
    return y;
}

//atan2()用于计算已知xy计算角度的函数