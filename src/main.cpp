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

#include "segcolors.h"
#include "getdepth_green.h"
#include "hough_round.h"
#include "deviation_angle.h"

#define PINK  1
#define WHITE 2
#define BLACK 3
#define BLUE  4
#define GREEN 5

//HSV的参数设定
int hmin_Max = 261;int hmax_Max = 360;
int smin_Max = 47 ;int smax_Max = 255;
int vmin_Max = 0  ;int vmax_Max = 255;
//霍夫参数设定
int hough_minDist = 75;          //圆心之间的最小距离= 70
int hough_canny = 20;            //canny边缘检测算子的高阈值，而低阈值为高阈值的一半。= 100
int hough_addthersold = 40;      //检测阶段圆心的累加器阈值 是否完美的圆形 = 100
int hough_minRadius = 0;         //有默认值0，表示圆半径的最小值= 0
int hough_maxRadius = 30;        //有默认值0，表示圆半径的最大值= 0

/* using namespace cv;
using namespace std; */

int main()
{
    const char* depth_win="depth_Image1nit";
    namedWindow(depth_win,WINDOW_AUTOSIZE);
    const char* color_win="color_Image1nit";
    namedWindow(color_win,WINDOW_AUTOSIZE);
 
    //深度图像颜色map
    rs2::colorizer c;
    // Helper to colorize depth images
 
    //想要获取的位置
    int centerLocation_x = 320;
    int centerLocation_y = 240;

    //循环中的变量
    Mat segcolor_pic;
    Mat result;
    int ball_color;

    //创建数据管道
    rs2::pipeline pipe;
    rs2::config pipe_config;
    pipe_config.enable_stream(RS2_STREAM_DEPTH,640,480,RS2_FORMAT_Z16,30);
    pipe_config.enable_stream(RS2_STREAM_COLOR,640,480,RS2_FORMAT_BGR8,30);
 
    //start()函数返回数据管道的profile
    rs2::pipeline_profile profile = pipe.start(pipe_config);
 
    //定义一个变量去转换深度到距离
    float depth_clipping_distance = 1.f;
 
    //声明数据流
    auto depth_stream=profile.get_stream(RS2_STREAM_DEPTH).as<rs2::video_stream_profile>();
    auto color_stream=profile.get_stream(RS2_STREAM_COLOR).as<rs2::video_stream_profile>();
 
    //获取内参
    auto intrinDepth=depth_stream.get_intrinsics();
    auto intrinColor=color_stream.get_intrinsics();
 
    //直接获取从深度摄像头坐标系到彩色摄像头坐标系的欧式变换矩阵
    auto  extrinDepth2Color=depth_stream.get_extrinsics_to(color_stream);

 
    while (cvGetWindowHandle(depth_win)&&cvGetWindowHandle(color_win)) // Application still alive?
    {
        //堵塞程序直到新的一帧捕获
        rs2::frameset frameset = pipe.wait_for_frames();
        //取深度图和彩色图
        rs2::frame color_frame = frameset.get_color_frame();//processed.first(align_to);
        rs2::frame depth_frame = frameset.get_depth_frame();
        rs2::frame depth_frame_4_show = frameset.get_depth_frame().apply_filter(c);
        //获取宽高
        const int depth_w=depth_frame.as<rs2::video_frame>().get_width();
        const int depth_h=depth_frame.as<rs2::video_frame>().get_height();
        const int color_w=color_frame.as<rs2::video_frame>().get_width();
        const int color_h=color_frame.as<rs2::video_frame>().get_height();
 
        //创建OPENCV类型 并传入数据
        Mat depth_image(Size(depth_w,depth_h),
                                CV_16U,(void*)depth_frame.get_data(),Mat::AUTO_STEP);
        Mat depth_image_4_show(Size(depth_w,depth_h),
                                CV_8UC3,(void*)depth_frame_4_show.get_data(),Mat::AUTO_STEP);
        Mat color_image(Size(color_w,color_h),
                                CV_8UC3,(void*)color_frame.get_data(),Mat::AUTO_STEP);

        ball_color = BLACK;
        switch (ball_color){
            case PINK :
                //HSV滤色的参数设定
                  hmin_Max = 261;  
                  hmax_Max = 360;
                  smin_Max = 47 ;  
                  smax_Max = 255;
                  vmin_Max = 0  ;  
                  vmax_Max = 255;
                //霍夫参数设定
                  hough_minDist = 75;          //圆心之间的最小距离= 70
                  hough_canny = 20;            //canny边缘检测算子的高阈值，而低阈值为高阈值的一半。= 100
                  hough_addthersold = 40;      //检测阶段圆心的累加器阈值 是否完美的圆形 = 100
                  hough_minRadius = 0;         //有默认值0，表示圆半径的最小值= 0
                  hough_maxRadius = 30;        //有默认值0，表示圆半径的最大值= 0
                break;

            case WHITE :
                //HSV滤色的参数设定
                hmin_Max =  0 ;  
                hmax_Max = 360;
                smin_Max = 0  ;  
                smax_Max = 255;
                vmin_Max = 0  ;  
                vmax_Max = 100;
                //霍夫参数设定
                hough_minDist = 75;          //圆心之间的最小距离= 70
                hough_canny = 20;            //canny边缘检测算子的高阈值，而低阈值为高阈值的一半。= 100
                hough_addthersold = 40;      //检测阶段圆心的累加器阈值 是否完美的圆形 = 100
                hough_minRadius = 0;         //有默认值0，表示圆半径的最小值= 0
                hough_maxRadius = 30;        //有默认值0，表示圆半径的最大值= 0
                break;

            case BLUE :

                break;
            case GREEN :

                break;
            case BLACK :
                //HSV滤色的参数设定
                hmin_Max =  0 ;  
                hmax_Max = 360;
                smin_Max = 0  ;  
                smax_Max = 255;
                vmin_Max = 0  ;  
                vmax_Max = 75;
                //霍夫参数设定
                hough_minDist = 500;          //圆心之间的最小距离= 70
                hough_canny = 55;            //canny边缘检测算子的高阈值，而低阈值为高阈值的一半。= 100
                hough_addthersold = 40;      //检测阶段圆心的累加器阈值 是否完美的圆形 = 100
                hough_minRadius = 0;         //有默认值0，表示圆半径的最小值= 0
                hough_maxRadius = 30;        //有默认值0，表示圆半径的最大值= 0
                break;

            default:
                break;
        }

                              
        //用测好的参数来HSV分割， trickbar参数测量在 hsv分割地面（保留）
        segcolor_pic = segmentation_HSV(hmin_Max , hmax_Max, 
            smin_Max, smax_Max, vmin_Max, vmax_Max, color_image);
        namedWindow("segcolor");imshow("segcolor", segcolor_pic);

        //找到圆  color_image
        vector<Vec3f> circles = houghRound_circles(segcolor_pic, 
            hough_minDist, hough_canny, hough_addthersold, hough_minRadius, hough_maxRadius);

        namedWindow("color_image");imshow("color_image", color_image);
        //实现深度图对齐到彩色图
        result = align_Depth2Color(depth_image,color_image,profile);
        //找到的圆的数量：
        if(circles.size() != 0)
        {
            centerLocation_x = cvRound(circles[0][0]);
            centerLocation_y = cvRound(circles[0][1]);
        }
        //测量距离
        measure_distance(color_image,result,cv::Size(20,20),profile,centerLocation_x,centerLocation_y);
        //测量角度
        cout<<deviation_angle_x(centerLocation_x,centerLocation_y)<<"\t"<<
        deviation_angle_y(centerLocation_x,centerLocation_y)<<endl;
        //显示
        imshow(depth_win,depth_image_4_show);
        imshow(color_win,color_image);

        namedWindow("result");imshow("result",result);
        waitKey(1);
    }

    return 0;
}
 