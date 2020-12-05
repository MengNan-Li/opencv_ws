#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
using namespace std;
using namespace cv;
#define WINDOW_NAME "threashold"
int thresholdValue = 100;
int thresholdType = 3; //cv::ThresholdTypes 模式1：反二进制阈值；模式2：截断阈值；模式3：反阈值化为0；模式4：阈值化为0
Mat srcImage, grayImage, dstImage;


void on_Threshold(int , void*){
  threshold(grayImage, dstImage, thresholdValue, 255, thresholdType);
  imshow(WINDOW_NAME, dstImage);
}

int main(int argc, char **argv){
  srcImage = imread("../lenna.jpg");
  if(!srcImage.data){
    printf("读取原图片出错！\n");
  }
  namedWindow(WINDOW_NAME);
  cvtColor(srcImage, grayImage, COLOR_RGB2GRAY);
  createTrackbar("mode type", WINDOW_NAME, &thresholdType, 4, on_Threshold);
  createTrackbar("threshold value", WINDOW_NAME, &thresholdValue, 255, on_Threshold);
  on_Threshold(0, 0);

  while(waitKey(8) != 'q')
    ;
  return 0;
}
