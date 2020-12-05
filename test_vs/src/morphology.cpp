#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/** 形态学：腐蚀和膨胀
 * 分割(isolate)独立的图像元素，以及连接(join)相邻的元素.寻找图像中的明显的极大值区域或极小值区域
 * 其他形态学操作，例如开运算、闭运算、形态学梯度、顶帽、黑帽，都可以使用morphologyEX函数完成
 * */

class Morphology {
public:
  Morphology(Mat &s, int trackbarN, int ks) : srcImage(s){
    trackbarNumber = trackbarN;
    kernalSize = ks;
  }
  ~Morphology() {}

  /*自定义的腐蚀膨胀操作*/
  void process() {
    //获取自定义kernal
    Mat kernal = getStructuringElement(
        MORPH_RECT, Size(2 * kernalSize + 1, 2 * kernalSize + 1),
        Point(kernalSize, kernalSize));
    if (trackbarNumber == 0) {
      erode(srcImage, dstImage, kernal);
    }
    if (trackbarNumber == 1) {
      dilate(srcImage, dstImage, kernal);
    }
    imshow("dstImage", dstImage);
		imshow("srcImage", srcImage);
    trackbar_change = false;
  }

  /*窗口设置*/
  void set_window() {
    namedWindow("srcImage");
    namedWindow("dstImage");
    //创建滚动条
    createTrackbar("erode/dilate", "dstImage", &trackbarNumber, 1,
                   on_trackbarNumber_change);
    createTrackbar("kernalSize", "dstImage", &kernalSize, 21,
                   on_kernalSize_change);
  }
  // creatTrackbard的callback函数中参数不会有this，但是类中的成员函数会有一个默认的this，使用静态函数就不会有了
  static void on_trackbarNumber_change(int, void *) { trackbar_change = true; }
  static void on_kernalSize_change(int, void *) { trackbar_change = true; }
  static bool trackbar_change;

private:
  Mat &srcImage, dstImage;
  int trackbarNumber; // 0表示erode, 1表示dilate
  int kernalSize;
};
bool Morphology::trackbar_change = false;

int main(int argc, char **argv) {
  Mat s = imread("../lenna.jpg");
  Morphology morphology(s, 1, 3);
	morphology.set_window();
  while (char(waitKey(1)) != 'q') {
    if (morphology.trackbar_change) {
      morphology.process();
    }
  }

  return 0;
}
