/*=================================================================
 * Calculate Background Model of a list of Frames(Normally a video stream) in the
 * method of Background Difference Method & OTSU Algorithm By OpenCV.
 *
 * Copyright (C) 2017 Chandler Geng. All rights reserved.
 *
 *     This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as published
 * by the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 *
 *     This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 *     You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc., 59
 * Temple Place, Suite 330, Boston, MA 02111-1307 USA
===================================================================
*/

/*=================================================
 * Version:
 * v1.0: 原版程序由IplImage转换为Mat；
 * v1.1: 背景差分法封装成类: BGDiff；
 * v1.2: 补充注释；
 * v1.3: 该方法与高斯混合背景模型不同，命名有误，改为背景差分法；
===================================================
*/

#include "BGDifference.h"

void unevenLightCompensate(Mat &image, int blockSize)
{
  if (image.channels() == 3)
    cvtColor(image, image, 7);
  double average = mean(image)[0];
  int rows_new = ceil(double(image.rows) / double(blockSize));
  int cols_new = ceil(double(image.cols) / double(blockSize));
  Mat blockImage;
  blockImage = Mat::zeros(rows_new, cols_new, CV_32FC1);
  for (int i = 0; i < rows_new; i++)
  {
    for (int j = 0; j < cols_new; j++)
    {
      int rowmin = i * blockSize;
      int rowmax = (i + 1) * blockSize;
      if (rowmax > image.rows)
        rowmax = image.rows;
      int colmin = j * blockSize;
      int colmax = (j + 1) * blockSize;
      if (colmax > image.cols)
        colmax = image.cols;
      Mat imageROI = image(Range(rowmin, rowmax), Range(colmin, colmax));
      double temaver = mean(imageROI)[0];
      blockImage.at<float>(i, j) = temaver;
    }
  }
  blockImage = blockImage - average;
  Mat blockImage2;
  resize(blockImage, blockImage2, image.size(), (0, 0), (0, 0), INTER_CUBIC);
  Mat image2;
  image.convertTo(image2, CV_32FC1);
  Mat dst = image2 - blockImage2;
  dst.convertTo(image, CV_8UC1);
}

int main(int argc, char **argv)
{
  // 原图像
  Mat pFrame;
  // 原始OTSU算法输出图像
  Mat pFroundImg;
  // 背景图像
  Mat pBackgroundImg;
  // 改进的OTSU算法输出图像
  Mat pFroundImg_c;
  Mat pBackgroundImg_c;
  BGDiff BGDif;

  pBackgroundImg = imread("../resources/bg.jpg");
  // unevenLightCompensate(pBackgroundImg, 12);
  cvtColor(pBackgroundImg, pBackgroundImg, COLOR_BGR2GRAY);
  medianBlur(pBackgroundImg, pBackgroundImg, 7);
  imshow("Background Image", pBackgroundImg);

  pFrame = imread("../resources/current.jpg");
  // unevenLightCompensate(pFrame, 12);
  cvtColor(pFrame, pFrame, COLOR_BGR2GRAY);
  medianBlur(pFrame, pFrame, 7);
  imshow("Current Image", pFrame);

  // absdiff(pFrame, pBackgroundImg, pFroundImg);
  BGDif.BackgroundDiff_lmn(pFrame, pFroundImg, pBackgroundImg, THRESH_BINARY);
  Mat element = getStructuringElement(MORPH_RECT, Size(7, 7));

  // erode(pFroundImg, pFroundImg, element);
  morphologyEx(pFroundImg, pFroundImg, MORPH_OPEN, element);
  element = getStructuringElement(MORPH_RECT, Size(30, 30));
  morphologyEx(pFroundImg, pFroundImg, MORPH_DILATE, element);

  /* 查找轮廓 */
  vector<vector<Point>> contours;
  vector<Vec4i> hierarchy;
  // Canny();
  Mat dstImage = Mat::zeros(pFroundImg.rows, pFroundImg.cols, CV_8UC3);
  findContours(pFroundImg, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
  int index = 0;
  for (; index >= 0; index = hierarchy[index][0])
  {
    Scalar color(rand() & 255, rand() & 255, rand() & 255);
    drawContours(dstImage, contours, index, color, 1, 8, hierarchy);
  }

  imshow("Front Image", dstImage);
  int nFrmNum = 1;

  // // OpenCV自带OTSU
  // BGDif.BackgroundDiff(pFrame, pFroundImg, pBackgroundImg, nFrmNum, CV_THRESH_OTSU);
  // // 阈值筛选后的OTSU
  // BGDif.BackgroundDiff(pFrame, pFroundImg_c, pBackgroundImg_c, nFrmNum, CV_THRESH_BINARY);

  // pFrame = imread("../../Image/current.jpg");
  // unevenLightCompensate(pFrame, 12);
  // nFrmNum = 2;

  // // OpenCV自带OTSU
  // BGDif.BackgroundDiff(pFrame, pFroundImg, pBackgroundImg, nFrmNum, CV_THRESH_OTSU);
  // // 阈值筛选后的OTSU
  // BGDif.BackgroundDiff(pFrame, pFroundImg_c, pBackgroundImg_c, nFrmNum, CV_THRESH_BINARY);

  // // 显示图像
  // imshow("Source Video", pFrame);
  // imshow("Background", pBackgroundImg);
  // imshow("OTSU ForeGround", pFroundImg);
  // imshow("Advanced OTSU ForeGround", pFroundImg_c);

  waitKey(0);
  return 0;
}
