#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;
using namespace std;
Mat srcImage, midImage, dstImage;
vector<Vec4i> lines;
int g_threshold = 100;

void on_HoughLines(int, void*){
  Mat dstI = dstImage.clone();
  Mat midI = midImage.clone();
  vector<Vec4i> mylines;
  HoughLinesP(midI, mylines, 1, CV_PI/180, g_threshold+1, 50, 10);
  //循环遍历绘制每一条线段
  for(size_t i=0; i<mylines.size(); i++){
    Vec4i l = mylines[i];
    line(dstI, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(23, 180, 55), 1, 16);
  }
  imshow("dstImage", dstI);
}

int main(int argc, char **argv){
  srcImage = imread("../lenna.jpg");
  namedWindow("srcImage");
  imshow("srcImage", srcImage);
  namedWindow("dstImage");
  createTrackbar("参数值", "dstImage", &g_threshold, 200, on_HoughLines);

  //进行边缘检测和转化为效果图
  Canny(srcImage, midImage, 50, 200, 3);
  cvtColor(midImage, dstImage, COLOR_GRAY2BGR);
  //调用一次回调函数，调用一次HoughLinesP函数
  on_HoughLines(g_threshold, 0);
  HoughLinesP(midImage, lines, 1, CV_PI/180, 80, 50, 10);
  imshow("dstImage", dstImage);
  while(waitKey(8) != 'q'){
    ;
  }
  return 0;
}