#include "segcolors.h"

using namespace std;
using namespace cv;

//HSV的参数设定
int hmin_Max_seg = 360;int hmax_Max_seg = 360;
int smin_Max_seg = 255;int smax_Max_seg = 255;
int vmin_Max_seg = 255;int vmax_Max_seg = 255;

//用测好的参数来HSV分割， trickbar参数测量在 hsv分割地面（保留） 
Mat segmentation_HSV(int hmin, int hmax, int smin, int smax, 
					 int vmin, int vmax, Mat input)
{
	Mat output, hsv_bgr_gnd, hsv_hsv_gnd, hsv_dst_gnd;
	if (!input.data || input.channels() != 3)
	{

		//报错	
	}
	//彩色图像的灰度值归一化
	input.convertTo(hsv_bgr_gnd, CV_32FC3, 1.0 / 255, 0);
	//颜色空间转换
	cvtColor(hsv_bgr_gnd, hsv_hsv_gnd, COLOR_BGR2HSV);

	//输出图像分配内存，新的黑色Mat
	hsv_dst_gnd = Mat::zeros(input.size(), CV_32FC3);
	//掩码
	Mat mask;
    //二值化
	inRange(hsv_hsv_gnd, Scalar(hmin, smin / float(smin_Max_seg), vmin / float(vmin_Max_seg)), 
    		Scalar(hmax, smax / float(smax_Max_seg), vmax / float(vmax_Max_seg)), mask);

	//只保留
	for (int r = 0; r < hsv_bgr_gnd.rows; r++)
	{
		for (int c = 0; c < hsv_bgr_gnd.cols; c++)
		{
			if (mask.at<uchar>(r, c) == 255)
			{
				//只将255写入空白的mask
				hsv_dst_gnd.at<Vec3f>(r, c) = hsv_bgr_gnd.at<Vec3f>(r, c);
			}
		}
	}
	//保存图像
	hsv_dst_gnd.convertTo(hsv_dst_gnd, CV_8UC3, 255.0, 0);
	output = hsv_dst_gnd;
	return output;
}