#include <opencv2/opencv.hpp>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;
using namespace cv;
//直方图比对
bool compareFacesByHist(Mat img,Mat orgImg)
{
	Mat tmpImg;
	resize(img, tmpImg, Size(orgImg.cols, orgImg.rows));
	imshow("Img1", img);
	imshow("tmpImg", tmpImg);
	imshow("orgImg", orgImg);
	//HSV颜色特征模型(色调H,饱和度S，亮度V)
	cvtColor(tmpImg, tmpImg, COLOR_BGR2HSV);
	cvtColor(orgImg, orgImg, COLOR_BGR2HSV);
	//直方图尺寸设置
	//一个灰度值可以设定一个bins，256个灰度值就可以设定256个bins
	//对应HSV格式,构建二维直方图
	//每个维度的直方图灰度值划分为256块进行统计，也可以使用其他值
	int hBins = 256, sBins = 256;
	int histSize[] = { hBins,sBins };
	//H:0~180, S:0~255,V:0~255
	//H色调取值范围
	float hRanges[] = { 0,180 };
	//S饱和度取值范围
	float sRanges[] = { 0,255 };
	const float* ranges[] = { hRanges,sRanges };
	int channels[] = { 0,1 };//二维直方图
	MatND hist1, hist2;
	calcHist(&tmpImg, 1, channels, Mat(), hist1,2,histSize, ranges, true, false);
	normalize(hist1, hist1, 0, 1, NORM_MINMAX, -1, Mat());
	calcHist(&orgImg, 1, channels, Mat(), hist2, 2, histSize, ranges, true, false);
	normalize(hist2, hist2, 0, 1, NORM_MINMAX, -1, Mat());
	double similarityValue = compareHist(hist1, hist2, CV_COMP_CORREL);
	cout << "相似度：" << similarityValue << endl;
	if (similarityValue >= 0.85)
	{
		return true;
	}
	return false;
}

int main()
{
	Mat orgImg = imread("/home/lmn/cabinet_imgs/2020-06-04-14-47-24.png");
	Mat img = imread("/home/lmn/cabinet_imgs/2020-06-04-14-48-10.png");
	compareFacesByHist(img, orgImg);
	waitKey(0);
	return 0;
}
