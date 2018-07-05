#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main(int argc, char **argv) {
  Mat srcImage = imread("../logo.png");
  if (!srcImage.data) {
    printf("srcImage is empty! \n");
    return 1;
  }
	// namedWindow("src");
	// imshow("src", srcImage);
  Mat logo = imread("../lenna.jpg");
  Mat mask = imread("../lenna.jpg", 0);
  if (!logo.data) {
    printf("headimage is empty! \n");
    return 1;
  }
	//ROI设置方法一：使用矩形框
  // Mat ROI = srcImage(Rect(2, 2, logo.cols, logo.rows));
	//ROI设置方法二：使用Range表示几行到几行，几列到几列的一个矩形范围
	Mat ROI = srcImage(Range(2, 2+logo.cols), Range(2, 2+logo.rows));

  
  logo.copyTo(ROI, mask);
  namedWindow("ROI");
  imshow("ROI", srcImage);
	waitKey(0);
  return 0;
}