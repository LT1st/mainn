#include <iostream>
#include <string>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

//用测好的参数来HSV分割， trickbar参数测量在 hsv分割地面（保留） 
Mat segmentation_HSV(int hmin, int hmax, int smin, int smax, 
					 int vmin, int vmax, Mat input);