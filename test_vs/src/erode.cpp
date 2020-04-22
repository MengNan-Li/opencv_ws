#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <vector>
using namespace cv;
using namespace std;

void ManyImages(vector<Mat> Images, Mat &dst, int imgRows) {
  int Num = Images.size(); //得到Vector容器中图片个数
  //设定包含这些图片的窗口大小，这里都是BGR3通道，如果做灰度单通道，稍微改一下下面这行代码就可以
  Mat Window(300 * ((Num - 1) / imgRows + 1), 300 * imgRows, CV_8UC3,
             Scalar(0, 0, 0));
  Mat Std_Image;                  //存放标准大小的图片
  Mat imageROI;                   //图片放置区域
  Size Std_Size = Size(300, 300); //每个图片显示大小300*300
  int x_Begin = 0;
  int y_Begin = 0;
  for (int i = 0; i < Num; i++) {
    x_Begin = (i % imgRows) * Std_Size.width; //每张图片起始坐标
    y_Begin = (i / imgRows) * Std_Size.height;
    resize(Images[i], Std_Image, Std_Size, 0, 0,
           INTER_LINEAR); //将图像设为标准大小
    //将其贴在Window上
    imageROI = Window(Rect(x_Begin, y_Begin, Std_Size.width, Std_Size.height));
    Std_Image.copyTo(imageROI);
  }
  dst = Window;
}

int main(int argc, char **argv) {
  Mat img = imread("../headimage.png");
//   imshow("原图", img);

  Mat ellemet = getStructuringElement(MORPH_RECT, Size(15, 15));
  Mat dist;
  erode(img, dist, ellemet);

  vector<Mat> manyimgV;
  manyimgV.push_back(img);
  manyimgV.push_back(dist);
  //imshow("腐蚀", dist);
  Mat mm;
  ManyImages(manyimgV, mm, 1);
  imshow("腐蚀对比", mm);
  waitKey(0);
  return 0;
}