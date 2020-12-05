#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

/**
 * 图片缩放：resize、pyrUp、pryDown
 **/
#define WINDOW_NAME "window"
Mat srcImage, dstImage, tmpImage;
int main(int argc, char **argv) {
  srcImage = imread("../lenna.jpg");
  if (!srcImage.data) {
    printf("读取srcImage出错！\n");
    return false;
  }
  namedWindow(WINDOW_NAME, WINDOW_AUTOSIZE);
  imshow(WINDOW_NAME, srcImage);

  //参数赋值
  tmpImage = srcImage;
  dstImage = srcImage;
  int key = 0;
  while (1) {
    key = waitKey(9);
    switch (key) {
    case '1':
      resize(tmpImage, dstImage, Size(tmpImage.cols / 2, tmpImage.rows / 2));
      printf("检测到按键1，开始进行基于resize函数的图片缩小\n");
      break;
    case '2':
      resize(tmpImage, dstImage, Size(tmpImage.cols * 2, tmpImage.rows * 2));
      printf("检测到按键2，开始进行基于resize函数的图片放大\n");
      break;
    case '3':
      pyrDown(tmpImage, dstImage, Size(tmpImage.cols / 2, tmpImage.rows / 2));
      printf("检测到按键3，开始进行基于pyrDown函数的图片缩小\n");
      break;
    case '4':
      pyrUp(tmpImage, dstImage, Size(tmpImage.cols * 2, tmpImage.rows * 2));
      printf("检测到按键4，开始进行基于PyrUp函数的图片放大\n");
      break;
    }
    imshow(WINDOW_NAME, dstImage);
    tmpImage = dstImage;
  }

  return 0;
}