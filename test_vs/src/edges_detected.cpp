#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

Mat srcImage, grayImage, dstImage;
// Canny边缘检测相关变量
Mat cannyDetectedEdges;
int cannyLowThreshold = 1; // trackbar位置参数
void on_Canny(int, void *) {
  //先使用3*3内核来降噪
  blur(srcImage, cannyDetectedEdges, Size(3, 3));
  //运行Canny算子
  Canny(cannyDetectedEdges, cannyDetectedEdges, cannyLowThreshold,
        cannyLowThreshold * 3, 3);
  //先将dstImage内的所有元素设置为0
  dstImage = Scalar::all(0);
  //使用Canny算子检测出来的边缘图作为掩码，来将原图拷贝到目标图中
  srcImage.copyTo(dstImage, cannyDetectedEdges);
  imshow("Canny", dstImage);
}

Mat sobelGradient_X, sobelGradient_Y;
Mat sobelAbsGradient_X, sobelAbsGradient_Y;
int sobelKernelSize = 1;
void on_Sobel(int, void*){
  //求X方向的梯度
  Sobel(srcImage, sobelGradient_X, CV_16S, 1, 0, (2*sobelKernelSize+1), 1, 1);
  convertScaleAbs(sobelGradient_X, sobelAbsGradient_X); //计算绝对值，将结果转化成8位
  //求Y方向的梯度
  Sobel(srcImage, sobelGradient_Y, CV_16S, 0, 1, (2*sobelKernelSize+1), 1, 1);
  convertScaleAbs(sobelGradient_Y, sobelAbsGradient_Y); //计算绝对值，将结果转化成8位
  //合并梯度
  addWeighted(sobelAbsGradient_X, 0.5, sobelAbsGradient_Y, 0.5, 0, dstImage);
  imshow("Sobel", dstImage);
}

Mat scharrGradient_X, scharrGradient_Y;
Mat scharrAbsGradient_X, scharrAbsGradient_Y;
//封装了Scharr边缘检测的函数
void Scharr(){
  //求X方向的梯度
  Scharr(srcImage, scharrGradient_X, CV_16S, 1, 0, 1, 0);
  convertScaleAbs(scharrGradient_X, scharrAbsGradient_X);//计算绝对值，并将结果转化成8位
  //求Y方向的梯度
  Scharr(srcImage, scharrGradient_Y, CV_16S, 0, 1, 1, 0);
  convertScaleAbs(scharrGradient_Y, scharrAbsGradient_Y);//计算绝对值，并将结果转化成8位 
  //合并梯度
  addWeighted(scharrAbsGradient_X, 0.5, scharrAbsGradient_Y, 0.5, 0, dstImage);
  imshow("Scharr", dstImage);
}

int main(int argc, char **agrv) {
  srcImage = imread("../lenna.jpg");
  if (!srcImage.data) {
    printf("读取原图像出错！\n");
    return false;
  }
  namedWindow("srcImage");
  imshow("srcImage", srcImage);
  // dstImage创建与原图像一样大小
  dstImage.create(srcImage.size(), srcImage.type());
  //将原图像转灰度图像
  cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);
  namedWindow("Canny");
  createTrackbar("参数值：", "Canny", &cannyLowThreshold, 120, on_Canny);
  namedWindow("Sobel");
  createTrackbar("参数值：", "Sobel", &sobelKernelSize, 3, on_Sobel);

  on_Canny(0,0);
  on_Sobel(0,0);

  namedWindow("Scharr");
  Scharr();

  while (waitKey(6) != 'q')
    ;
  return 0;
}