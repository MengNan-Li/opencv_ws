#ifndef COMBINE_IMAGES_HPP
#define COMBINE_IMAGES_HPP
#include <opencv2/core.hpp>
#include <iostream>
using namespace cv;

Mat combineImages(std::vector<Mat> imgs,//@parameter1:需要显示的图像组 
                  int col,//parameter2:显示的列数
                  int row, //parameter3:显示的行数
                  bool hasMargin, //parameter4:是否设置边框
                  bool gray, //parameter5:是否是灰度图
                  float zoom = 1.0){ //0.1-1
    int imgAmount = imgs.size();//获取需要显示的图像数量
    int width = imgs[0].cols;//本函数默认需要显示的图像大小相同
    int height = imgs[0].rows;//获取图像宽高
    int newWidth, newHeight;//新图像宽高
    if (!hasMargin){
        newWidth = col*imgs[0].cols;//无边框，新图像宽/高=原图像宽/高*列/行数
        newHeight = row*imgs[0].rows;
    }
    else{
        newWidth = (col + 1) * 20 + col*width;//有边框，要将上边框的尺寸，这里设置边框为20px
        newHeight = (row + 1) * 20 + row*height;
    }

    Mat newImage;
    if(gray){
      newImage = Mat(newHeight, newWidth, CV_8UC1, cv::Scalar(255));
    }else{
      newImage = Mat(newHeight, newWidth, CV_8UC3, cv::Scalar(255, 255, 255));
    }

    int x, y,imgCount;//x列号，y行号，imgCount图片序号
    if (hasMargin){//有边框
        imgCount = 0;
        x = 0; y = 0;
        while (imgCount < imgAmount){
            Mat imageROI = newImage(Rect(x*width + (x + 1) * 20, y*height + (y + 1) * 20, width, height));//创建感兴趣区域
            imgs[imgCount].copyTo(imageROI);//将图像复制到大图中
            imgCount++;
            if (x == (col - 1)){
                x = 0;
                y++;
            }
            else{
                x++;
            }//移动行列号到下一个位置
        }
    }
    else{//无边框
        imgCount = 0;
        x = 0; y = 0;
        while (imgCount < imgAmount){
            Mat imageROI = newImage(Rect(x*width, y*height, width, height));
            imgs[imgCount].copyTo(imageROI);
            imgCount++;
            if (x == (col - 1)){
                x = 0;
                y++;
            }
            else{
                x++;
            }
        }
    }
    cv::Mat outImage;
    cv::resize(newImage, outImage, cv::Size(0, 0), zoom, zoom);
    return outImage;//返回新的组合图像
}

#endif