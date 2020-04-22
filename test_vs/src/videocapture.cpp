#include <opencv2/opencv.hpp>
using namespace cv;
int main(int argc, char **argv){
  VideoCapture capture(argv[1]);
  Mat image;
  int count = capture.get(cv::CAP_PROP_FRAME_COUNT);
  int fps = capture.get(cv::CAP_PROP_FPS);
  std::cout<<count<<std::endl;
  std::cout<<fps<<std::endl;
  std::cout<<count/fps<<std::endl;
  // while (1)
	// {
    
	// 	//读取当前帧
	// 	capture.read(image);
  //   imshow("Container Video",image);
  //   waitKey(30);
  // }
}