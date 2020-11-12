#include <iostream>
#include <sstream>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
 
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/highgui/highgui_c.h>
 
#include <librealsense2/rs.hpp>
#include <librealsense2/rsutil.h>

using namespace cv;
using namespace std;

//获取深度像素对应长度单位（米）的换算比例
float get_depth_scale(rs2::device dev);

//深度图对齐到彩色图函数
Mat align_Depth2Color(Mat depth,Mat color,rs2::pipeline_profile profile);

//测量深度
void measure_distance(Mat &color,Mat depth,cv::Size range,rs2::pipeline_profile profile ,int x, int y);