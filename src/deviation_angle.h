#include <iostream>
#include <string>
#include <cmath>

/* #include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv; */



/*
输入：传入点的位置 double a,b
返回：相对于中心的x、y偏转角度
提升：提高精度，加入考虑三角形模型
参数：27.68 19.91
*/

double deviation_angle_x(double a, double b);

double deviation_angle_y(double a, double b);