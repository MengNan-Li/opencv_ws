#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;
#define WINDOW_WIDTH 600 //定义窗口大小的宏

void drawEllipse(Mat img, double angle) {
  int thickness = 2;
  int lineType = 8;
  ellipse(img, Point(WINDOW_WIDTH / 2, WINDOW_WIDTH / 2),
          Size(WINDOW_WIDTH / 4, WINDOW_WIDTH / 16), angle, 0, 360,
          Scalar(255, 129, 0), thickness, lineType);
}

void drawFilledCircle(Mat img, Point center) {
  circle(img, center, WINDOW_WIDTH / 2, Scalar(0, 0, 255), 2, 8);
}

int main(int argc, char **argv) {
  Mat atomImage = Mat::zeros(WINDOW_WIDTH, WINDOW_WIDTH, CV_8UC3);
  drawEllipse(atomImage, 0);
  drawEllipse(atomImage, 45);
  drawEllipse(atomImage, 90);
  drawEllipse(atomImage, 135);
  circle(atomImage, Point(WINDOW_WIDTH / 2, WINDOW_WIDTH / 2),
         WINDOW_WIDTH / 32, Scalar(0, 0, 255), 2, 8);

  imshow("draw", atomImage);
  waitKey(0);
  return 0;
}