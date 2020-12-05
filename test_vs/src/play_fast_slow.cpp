#include <opencv2/opencv.hpp>  
#include <iostream>
using namespace std;
using namespace cv;
 
#define WINDOW_NAME "【正在播放】"        //为窗口标题定义的宏 
 
int g_ndelay_ms=33;          //延时时间
int g_currentpercent;        //当前百分比
int g_ncurrentframe;         //当前帧
int g_nsetframe;             //设置当前帧
char g_nTrackbarName[50];    //用于存储显示内容 
int g_ntotalFrameNumber;     //总帧数
bool f_capture_update = false; //根据进度切换标志位
 
//-----------------------------------【on_Trackbar( )函数】--------------------------------
//		描述：响应滑动条的回调函数
//------------------------------------------------------------------------------------------
void on_Trackbar(int, void*)
{
	f_capture_update = true;
}
 
//-----------------------------------【ShowHelpText( )函数】----------------------------------
//		描述：输出一些帮助信息
//----------------------------------------------------------------------------------------------
void ShowHelpText()
{
	//输出欢迎信息和OpenCV版本
	printf("\n\n  ----------------------------------------------------------------------------");
	printf("\n\n\t\t\tCODE BY KAKA\n");
	printf("\n\n\t\t\tHELP:");
	printf("\n\n\t\t\t滑动进度条来实现进度切换");
	printf("\n\n\t\t\t按键空格(SPACE)切换停止/播放，ESC退出播放");
	printf("\n\n\t\t\t按键U-I-O切换播放速度，分别为高-中-低");
	printf("\n\n\t\t\t按键H(+)/J(-)自定义播放速度+/-");
	printf("\n\n\t\t\t按键K(+)/L(-)实现帧+/-");
	printf("\n\n\t\t\t按键W实现逐帧播放，空格（SPACE）退出");
	printf("\n\n\t\t\t   当前使用的OpenCV版本为：" CV_VERSION);
	printf("\n\n  ----------------------------------------------------------------------------\n");
}
//-----------------------------------【ImageText( )函数】----------------------------------
//		描述：把文字加在图像上 
//----------------------------------------------------------------------------------------------
void ImageText(Mat* img, const char* text, int x, int y)
{
	Point pt(x, y);
	Scalar color = CV_RGB(255, 255, 255);
	//purText()
	putText(*img, text, pt, CV_FONT_HERSHEY_SIMPLEX, 1, color, 1, 20);
}
 
//-----------------------------------【main( )函数】--------------------------------------------
//		描述：控制台应用程序的入口函数，我们的程序从这里开始
//-------------------------------------------------------------------------------------------------
int main()
{
	bool f_stop = false;
	bool f_nextstop = false;
	bool f_perframe = false;
	ShowHelpText();
	//【1】读入视频
	VideoCapture capture("/Users/lmn/Downloads/2020.02/20200217_211245_869012040106283_033.mp4");
	//【2】检测是否已经打开
	if (!capture.isOpened())
		cout << "fail to open!" << endl;
	//【3】检测总共帧数
	g_ntotalFrameNumber = capture.get(CV_CAP_PROP_FRAME_COUNT);
	cout << "整个视频共" << g_ntotalFrameNumber << "帧" << endl;
 
	namedWindow(WINDOW_NAME, 1);
	//【4】计算当前百分比
	g_currentpercent = g_ncurrentframe / g_ntotalFrameNumber * 100;;
	sprintf(g_nTrackbarName, "已播放", g_currentpercent);
	//【5】创建进度条
	createTrackbar(g_nTrackbarName, WINDOW_NAME, &g_currentpercent, 100, on_Trackbar);
	//结果在回调函数中显示
	on_Trackbar(g_ncurrentframe, 0);
 
	while (!f_stop)
	{
		Mat frame;//定义一个Mat变量，用于存储每一帧的图像
		Mat dstImage1;
		capture >> frame;  //读取当前帧
		//拖动滑动条后更新视频
		if (f_capture_update == true)
		{
			g_nsetframe = g_currentpercent * g_ntotalFrameNumber / 100;
			capture.set(CV_CAP_PROP_POS_FRAMES, g_nsetframe);
			g_ncurrentframe = g_nsetframe;
			f_capture_update = false;
		}
		g_ncurrentframe++;
		g_currentpercent = int(g_ncurrentframe *100 / g_ntotalFrameNumber);
		//setTrackbarPos() set进度条位置
		setTrackbarPos(g_nTrackbarName, WINDOW_NAME, g_currentpercent);
		//循环播放
		if (g_currentpercent == 100)
		{
			g_ncurrentframe = 0;
			g_ncurrentframe++;
			//capture.set() set视频进度
			capture.set(CV_CAP_PROP_POS_FRAMES, g_ncurrentframe);
		}
		//数字显示
		char text[4] ;
		sprintf(text, "%d", g_ncurrentframe);
		ImageText(&frame, text, 5, 25);
 
		imshow(WINDOW_NAME, frame);  //显示当前帧
		//退出逐帧
		if (f_nextstop == true)
		{
			while (waitKey(10) != 32)
				;
			f_nextstop = false;
		}
		//逐帧播放
		if (f_perframe == true)
		{
			char ch;
			while (ch=waitKey(10))
			{
				if (ch == 'w')			//ctrl
				{
					break;
				}
				else if (ch == 32)
				{
					f_perframe = false;
					break;
				}
			}
		}
		//控制延时实现快慢
		char c = (char)waitKey(g_ndelay_ms);  //延时30ms
		if (c == 27)
			f_stop = true;
		switch (c)
		{
		case 32:         //space播放/停止
			waitKey(0);
			//f_nextstop = false;
			break;
		case 'u':        //快速播放
			g_ndelay_ms = 10;
			break;
		case 'i':        //正常速度
			g_ndelay_ms = 33;
			break;
		case 'o':        //慢速
			g_ndelay_ms = 100;
			break;
		case 'h':        //速度+
			waitKey(0);
			if (g_ndelay_ms<=20)
				g_ndelay_ms++;
			else if (g_ndelay_ms>20 && g_ndelay_ms<=100)
				g_ndelay_ms+=20;
			else if (g_ndelay_ms>100)
				g_ndelay_ms += 50;
			waitKey(g_ndelay_ms);
			cout << "延时" << g_ndelay_ms << "ms" << endl;
			break;
		case 'j':       //速度- 
			waitKey(0);
			if (g_ndelay_ms<=20&&g_ndelay_ms>1)
				g_ndelay_ms--;
			else if (g_ndelay_ms>20 && g_ndelay_ms<=100)
				g_ndelay_ms -= 20;
			else if (g_ndelay_ms>100)
				g_ndelay_ms -= 50;
			cout << "延时" << g_ndelay_ms << "ms" << endl;
			waitKey(g_ndelay_ms);
			break;
		case 'k':       //帧数+
			g_ncurrentframe+=20;
			capture.set(CV_CAP_PROP_POS_FRAMES, g_ncurrentframe);
			cout << "第" << g_ncurrentframe << "帧" << endl;
			f_nextstop = true;
			break;
		case 'l':       //帧数-
			g_ncurrentframe-=20;
			capture.set(CV_CAP_PROP_POS_FRAMES, g_ncurrentframe);
			cout << "第" << g_ncurrentframe << "帧" << endl;
			break;
		case 'w':       //逐帧
			f_perframe = true;
		default:
			break;
		}
	}
	return 0;
}