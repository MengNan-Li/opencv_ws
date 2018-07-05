#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;
//用指针访问像素
void colorReduce(Mat &inputImage, Mat &outputImage, int div) {
  outputImage = inputImage.clone();
  for (int i = 0; i < outputImage.rows; i++) {
    uchar *data = outputImage.ptr<uchar>(i);
    for (int j = 0; j < outputImage.cols * outputImage.channels(); j++) {
      data[j] = data[j] / div * div + div / 32; //处理每个像素，缩减颜色空间
    }
  }
}

int main(int argc, char **argv) {
  Mat srcImage = imread("../headimage.png");
  Mat dstImage;
  dstImage.create(srcImage.rows, srcImage.cols, srcImage.type());
  double time0 = static_cast<double>(getTickCount());
  colorReduce(srcImage, dstImage, 32);
  time0 = (static_cast<double>(getTickCount()) - time0)/getTickFrequency();
  cout<<"此方法运行时间为："<<time0<<"秒"<<endl;
  cout<<dstImage.rows<<"    "<<dstImage.cols<<endl;
  imshow("效果图", dstImage);
  waitKey(0);
  return 0;
}