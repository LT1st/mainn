#include <iostream>
#include <string>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

vector<Vec3f> houghRound_circles(
            Mat dst_s,                      //传入的照片记得是彩色的
            int hough_minDist = 70,         //圆心之间的最小距离
            int hough_canny = 100,          //canny边缘检测算子的高阈值，而低阈值为高阈值的一半。
            int hough_addthersold = 100,    //检测阶段圆心的累加器阈值 是否完美的圆形 
            int hough_minRadius = 0,        //有默认值0，表示圆半径的最小值
            int hough_maxRadius = 0         //有默认值0，表示圆半径的最大值
);
