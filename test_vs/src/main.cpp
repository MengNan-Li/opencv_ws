#include "opencv/highgui.h"
int add(int a, int b){
  return a+b;
}
int main(int argc, char **argv) {
  // 是一个高层调用接口，它通过文件名确定被加载文件的格式；
  // 且该函数自动分配图像数据结构所需的内存。
  // cvLoadImage可以读取大多数格式的图像文件，BMP、DIB、JPEG、JPE、PNG、BBM、PPM
  // SR、RAS、TIFF
  // 函数执行完后返回一个指针，此指针指向一块为描述该图像文件的数据结构而分配的内存块。
  IplImage *img = cvLoadImage("/Users/lmn/opencv_ws/test_vs/headimage.png");
  //  cvNamedWindow由HighGUI库提供，用于在屏幕上创建一个窗口，将被显示的图像包含于该窗口中。
  // 函数第一个参数指定了窗口的的窗口标题。
  // 如果要使用HighGUI库所提供的其他函数与该窗口进行交互，我们将通过该参数值引用这个窗口中。
  cvNamedWindow("Example1", CV_WINDOW_AUTOSIZE);
  // 显示该图像
  cvShowImage("Example1", img);
  // 使程序暂停，等待用户触发一个按键操作，但如果该函数参数设为一个正数，则程序将暂停一段时间，
  // 时间长为该整数值个毫秒单位
  // 如果设置为0，那么将一直等待用户触发按键操作。
  cvWaitKey(0);
  // 内存释放功能
  cvReleaseImage(&img);
  int a = 1;
  a = 2;
  add(1,2);
  // 关闭窗口
  cvDestroyWindow("Example1");
}
