
#include <iostream>
#include <opencv2/opencv.hpp>
 
using namespace std;
using namespace cv;

#if CV_MAJOR_VERSION >= 4
#define CV_BGR2GRAY cv::COLOR_BGR2GRAY
#define CV_THRESH_BINARY cv::THRESH_BINARY
#define CV_CHAIN_APPROX_NONE cv::CHAIN_APPROX_NONE
#endif 

void RemoveSmallRegion(Mat &Src, Mat &Dst,int AreaLimit, int CheckMode, int NeihborMode)  
{  
    int RemoveCount = 0;  
    //新建一幅标签图像初始化为0像素点，为了记录每个像素点检验状态的标签，0代表未检查，1代表正在检查,2代表检查不合格（需要反转颜色），3代表检查合格或不需检查   
    //初始化的图像全部为0，未检查  
    Mat PointLabel = Mat::zeros(Src.size(), CV_8UC1);  
    if (CheckMode == 1)//去除小连通区域的白色点  
    {  
        cout << "去除小连通域.";  
        for (int i = 0; i < Src.rows; i++)  
        {  
            for (int j = 0; j < Src.cols; j++)  
            {  
                if (Src.at<uchar>(i, j) < 10)  
                {  
                    PointLabel.at<uchar>(i, j) = 3;//将背景黑色点标记为合格，像素为3  
                }  
            }  
        }  
    }  
    else//去除孔洞，黑色点像素  
    {  
        cout << "去除孔洞";  
        for (int i = 0; i < Src.rows; i++)  
        {  
            for (int j = 0; j < Src.cols; j++)  
            {  
                if (Src.at<uchar>(i, j) > 10)  
                {  
                    PointLabel.at<uchar>(i, j) = 3;//如果原图是白色区域，标记为合格，像素为3  
                }  
            }  
        }  
    }  
  
    vector<Point2i>NeihborPos;//将邻域压进容器  
    NeihborPos.push_back(Point2i(-1, 0));  
    NeihborPos.push_back(Point2i(1, 0));  
    NeihborPos.push_back(Point2i(0, -1));  
    NeihborPos.push_back(Point2i(0, 1));  
    if (NeihborMode == 1)  
    {  
        cout << "Neighbor mode: 8邻域." << endl;  
        NeihborPos.push_back(Point2i(-1, -1));  
        NeihborPos.push_back(Point2i(-1, 1));  
        NeihborPos.push_back(Point2i(1, -1));  
        NeihborPos.push_back(Point2i(1, 1));  
    }  
    else cout << "Neighbor mode: 4邻域." << endl;  
    int NeihborCount = 4 + 4 * NeihborMode;  
    int CurrX = 0, CurrY = 0;  
    //开始检测  
    for (int i = 0; i < Src.rows; i++)  
    {  
        for (int j = 0; j < Src.cols; j++)  
        {  
            if (PointLabel.at<uchar>(i, j) == 0)//标签图像像素点为0，表示还未检查的不合格点  
            {   //开始检查  
                vector<Point2i>GrowBuffer;//记录检查像素点的个数  
                GrowBuffer.push_back(Point2i(j, i));  
                PointLabel.at<uchar>(i, j) = 1;//标记为正在检查  
                int CheckResult = 0;  
  
  
                for (int z = 0; z < GrowBuffer.size(); z++)  
                {  
                    for (int q = 0; q < NeihborCount; q++)  
                    {  
                        CurrX = GrowBuffer.at(z).x + NeihborPos.at(q).x;  
                        CurrY = GrowBuffer.at(z).y + NeihborPos.at(q).y;  
                        if (CurrX >= 0 && CurrX<Src.cols&&CurrY >= 0 && CurrY<Src.rows)  //防止越界    
                        {  
                            if (PointLabel.at<uchar>(CurrY, CurrX) == 0)  
                            {  
                                GrowBuffer.push_back(Point2i(CurrX, CurrY));  //邻域点加入buffer    
                                PointLabel.at<uchar>(CurrY, CurrX) = 1;           //更新邻域点的检查标签，避免重复检查    
                            }  
                        }  
                    }  
                }  
                if (GrowBuffer.size()>AreaLimit) //判断结果（是否超出限定的大小），1为未超出，2为超出    
                    CheckResult = 2;  
                else  
                {  
                    CheckResult = 1;  
                    RemoveCount++;//记录有多少区域被去除  
                }  
  
  
                for (int z = 0; z < GrowBuffer.size(); z++)  
                {  
                    CurrX = GrowBuffer.at(z).x;  
                    CurrY = GrowBuffer.at(z).y;  
                    PointLabel.at<uchar>(CurrY,CurrX)+=CheckResult;//标记不合格的像素点，像素值为2  
                }  
                //********结束该点处的检查**********    
  
  
            }  
        }  
  
  
    }  
  
  
    CheckMode = 255 * (1 - CheckMode);  
    //开始反转面积过小的区域    
    for (int i = 0; i < Src.rows; ++i)  
    {  
        for (int j = 0; j < Src.cols; ++j)  
        {  
            if (PointLabel.at<uchar>(i,j)==2)  
            {  
                Dst.at<uchar>(i, j) = CheckMode;  
            }  
            else if (PointLabel.at<uchar>(i, j) == 3)  
            {  
                Dst.at<uchar>(i, j) = Src.at<uchar>(i, j);  
                  
            }  
        }  
    }  
    cout << RemoveCount << " objects removed." << endl;  
}  


int main()
{
	
	Mat currentframe, previousframe;
	Mat img1, img2, img3;
 
	img1 = imread("/home/lmn/ros_ws/runc_ws/datas/bg.png");
	img2 = imread("/home/lmn/ros_ws/runc_ws/datas/1.png");
	img3 = img2;
 
  GaussianBlur(img1, img1, cv::Size(3,3), 0);
  GaussianBlur(img2, img2, cv::Size(3,3), 0);
  Mat mask(img1.size(), img1.type(), Scalar(255));
  // imshow("img1",img1);
  // illuminationChange(img1,mask,img1, 0.1,0.2);
  // illuminationChange(img2,mask,img2, 0.1,0.2);
  // imshow("illuminationChange",img1);
	cvtColor(img1, previousframe, CV_BGR2GRAY);
	cvtColor(img2, currentframe, CV_BGR2GRAY);	//转化为单通道灰度图
 
	absdiff(currentframe, previousframe, currentframe);//做差求绝对值  
  
  imshow("absdiff", currentframe);
	threshold(currentframe, currentframe, 50, 255.0, CV_THRESH_BINARY);
  imshow("threshold", currentframe);


  Mat element = getStructuringElement(MORPH_RECT, Size(10, 10));
	dilate(currentframe, currentframe, element);
  erode(currentframe, currentframe, element);

  // morphologyEx(currentframe, currentframe, MORPH_OPEN, (3,3));
  // morphologyEx(currentframe, currentframe, MORPH_CLOSE, (10,10));
 
  // RemoveSmallRegion(currentframe,currentframe,20,1,1);

	imshow("foreground", currentframe);	//显示图像  
 
	vector<vector<Point> > v;
	vector<Vec4i> hierarchy;
	Mat result;
	Rect rect;
  vector<double> results_area;
	findContours(currentframe, v, hierarchy, RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	for (int i = 0; i < hierarchy.size(); i++)
	{
    double area = contourArea(v.at(i));
    // std::cout<<area<<std::endl;
    if(area > 30){
      results_area.push_back(area);
      rect = boundingRect(Mat(v.at(i)));
      // 画最小的圆，贴着黑色
      drawContours(img3, v, i, Scalar(0, 0, 255), 1, 8, hierarchy);
      // 画矩形包围圆
      rectangle(img3, rect.tl(), rect.br(), Scalar(0, 255, 0), 2);
    }

	}

  std::cout<<results_area.size()<<std::endl;
  for(double i : results_area){
    std::cout<<i<<" ";
  }
  std::cout<<std::endl;
 
	// imwrite("E:/res1.jpg", img3);
	imshow("moving area1", img3);
	
	//把当前帧保存作为下一次处理的前一帧  
	//cvtColor(tempframe, previousframe, CV_BGR2GRAY);
	waitKey(0);
	return 0;
 
}
