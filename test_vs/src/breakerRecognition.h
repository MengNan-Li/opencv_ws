#ifndef BREAKERRECOGNITION_H
#define BREAKERRECOGNITION_H

#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;


class breakerRecognition
{
    Mat srcImage, hsvImage, modelImage, aftRecognition;	//输入图像、输出图像、增强图像、识别图像
    string imagePath;			//图像存储路径
    string modelPath;
    string contourMatchPath;

    vector<vector<Point>> modelContour;		//模板轮廓
    vector<vector<Point>> imageContours;	//图像轮廓

public:
    breakerRecognition();
    bool getSrcImage();		//获取图像,并写入srcImage  1
    bool getModelImage();	//获取模板图像
    bool setsrcImage();		//本地图像写入srcImage
    bool setModelImage();	//写入modelImage  1

    vector<vector<Point>> getContour(Mat image);//轮廓提取  1

    Mat imageClip(Mat image);					//图像剪裁  1

    void histogramIntensification();			//图像增强:直方图(对比度)
    void laprasIntensification(Mat image);		//图像增强:lapras(锐化)	可选
    void logIntensification();					//图像增强:log(亮化)
    void gammaIntensification();				//图像增强:gamma(均衡化)

    bool colorRecognition();			//颜色识别,给出状态
    bool contourMatch();				//轮廓匹配  1
    bool contourSelect();				//轮廓选取  1

    bool showVedio();					//视频显示
};

#endif // BREAKERRECOGNITION_H
