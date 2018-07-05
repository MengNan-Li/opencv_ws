#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;
/**
 * 方框滤波：boxFilter
 * 均值滤波：blur
 * 高斯滤波，低通、模糊，高斯模糊：GaussianBlur
 * 此外还有：
 * 中值滤波模糊：medianBlur，比高斯的好处是不会使用噪点数据
 * 双边滤波：bilateralFilter，边缘保护好
*/

int main(int argc, char **argv){
    Mat srcImg = imread("../lenna.jpg");
    //中文名显示有问题，经常显示不出来
    namedWindow("srcImg");
    namedWindow("boxFilter-blur");
    namedWindow("blur");
    namedWindow("GaussianBlur");
    imshow("srcImg", srcImg);
    Mat outImg;
    boxFilter(srcImg, outImg, -1, Size(5, 5)); //默认参数normaliz=true, 则为均值滤波，否则为方框滤波
    imshow("boxFilter-blur", outImg);
    blur(srcImg, outImg, Size(5, 5));//均值滤波
    imshow("blur", outImg);
    GaussianBlur(srcImg, outImg, Size(5,5), 0, 0);
    imshow("GaussianBlur", outImg);
    waitKey(0);
    waitKey(0);
    waitKey();
    waitKey();
    return 0;
}