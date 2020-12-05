///运动物体检测——帧差法
#include "opencv2/opencv.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "combineImages.hpp"
using namespace cv;
#include <iostream>
using namespace std;
//运动物体检测函数声明
Mat MoveDetect(Mat temp, Mat frame);

int main()
{

  VideoCapture video("../resources/sku.avi");
  if (!video.isOpened())
  {
    cout << "video open error!" << endl;
    return 0;
  }
  Mat frame; //存储帧
  Mat temp;  //存储前一帧图像
  Mat result;
  video >> frame; //读帧进frame
  bool first = true;
  while (!frame.empty())
  { 
     GaussianBlur(frame,frame,Size(5,5),0,0);
    //存储结果图像
    int frameCount = video.get(CAP_PROP_FRAME_COUNT); //获取帧数
    double FPS = video.get(CAP_PROP_FPS);             //获取FPS
    // imshow("frame", frame);
    if (first) //如果为第一帧（temp还为空）
    {
      result = MoveDetect(frame, frame); //调用MoveDetect()进行运动物体检测，返回值存入result
    }
    else //若不是第一帧（temp有值了）
    {
      result = MoveDetect(temp, frame); //调用MoveDetect()进行运动物体检测，返回值存入result
    }
    // imshow("result", result);
    int key = waitKey(30);
    if (key == 27) //按原FPS显示
    {
      cout << "ESC退出!" << endl;
      break;
    }
    if(key == 32){
      //空格暂停
      waitKey(0);
    }
    temp = frame.clone();
    video >> frame; //读帧进frame
    first = false;
  }
  return 0;
}
Mat MoveDetect(Mat temp, Mat frame)
{
  Mat result = frame.clone();
  //1.将background和frame转为灰度图
  Mat gray1, gray2;
  cvtColor(temp, gray1, COLOR_BGR2GRAY);
  cvtColor(frame, gray2, COLOR_BGR2GRAY);
  //2.将background和frame做差
  Mat diff;
  absdiff(gray1, gray2, diff);
  // imshow("diff", diff);
  //3.对差值图diff_thresh进行阈值化处理
  Mat diff_thresh;
  threshold(diff, diff_thresh, 100, 255, THRESH_BINARY);
  // imshow("diff_thresh", diff_thresh);
  //4.腐蚀
  Mat kernel_erode = getStructuringElement(MORPH_RECT, Size(3, 3));
  Mat kernel_dilate = getStructuringElement(MORPH_RECT, Size(18, 18));
  Mat img_erode;
  Mat img_dilate;
  erode(diff_thresh, img_erode, kernel_erode);
  // imshow("erode", img_erode);
  //5.膨胀
  dilate(diff_thresh, img_dilate, kernel_dilate);
  // imshow("dilate", img_dilate);
  //6.查找轮廓并绘制轮廓
  vector<vector<Point>> contours;
  findContours(img_dilate, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);
  drawContours(result, contours, -1, Scalar(0, 0, 255), 2); //在result上绘制轮廓
  //7.查找正外接矩形
  vector<Rect> boundRect(contours.size());
  for (int i = 0; i < contours.size(); i++)
  {
    boundRect[i] = boundingRect(contours[i]);
    rectangle(result, boundRect[i], Scalar(0, 255, 0), 2); //在result上绘制正外接矩形
  }
  std::vector<cv::Mat> imgs1 = {frame, result};
  std::vector<cv::Mat> imgs2 = {diff, diff_thresh, img_dilate};
  imshow("FramesDifference", combineImages(imgs1, 2, 1, true, false, 0.5));
  imshow("gray", combineImages(imgs2, 3, 1, true, true, 0.5));
  return result; //返回result
}
