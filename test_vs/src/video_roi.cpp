#include <opencv2/opencv.hpp>
#include <iostream>
#include <sstream>
#include <fstream>
using namespace cv;
using namespace std;



Mat image;
Mat imageCopy; //绘制矩形框时用来拷贝原图的图像
bool leftButtonDownFlag=false; //左键单击后视频暂停播放的标志位
Point originalPoint; //矩形框起点
Point processPoint; //矩形框终点
bool  flag = false;


//鼠标回调函数  
void onMouse(int event,int x,int y,int flags,void *ustc)  
{     
 
	if(event==CV_EVENT_LBUTTONDOWN)  
	{  
		flag = true;
		leftButtonDownFlag=true; //标志位
		originalPoint=Point(x,y);  //设置左键按下点的矩形起点
		if(originalPoint.x+80>320){
			originalPoint.x = 240;
		}
		if(originalPoint.y+80>240){
			originalPoint.y = 160;
		}	
		processPoint=originalPoint;
	}  
	if(event==CV_EVENT_MOUSEMOVE&&leftButtonDownFlag)  
	{  		
		processPoint=Point(x,y);	
    // imageCopy=image.clone();
		// processPoint=Point(x,y);
		// if(originalPoint!=processPoint)
		// {
		// 	//在复制的图像上绘制矩形
		// 	rectangle(imageCopy,originalPoint,processPoint,Scalar(255,0,0),2);
		// }
		// imshow("Friends",imageCopy);	
	}  
	if(event==CV_EVENT_LBUTTONUP)  
	{  
		leftButtonDownFlag=false;

		// Mat rectImage=image(Rect(originalPoint,processPoint)); //子图像显示
		// imshow("Sub Image",rectImage);		 
	}	 
} 

static vector<string> split_str(string str, string pattern)
{
    string::size_type pos;
    vector<string> result;
    str += pattern;
    size_t size = str.size();
    for(size_t i = 0; i < size; i++)
    {
        pos = str.find(pattern,i);
        if(pos < size)
        {
            string s = str.substr(i,pos-i);
            result.push_back(s);
            i = pos + pattern.size() - 1;
        }
    }
    return result;
}


int main(int argc, char **argv) {

	int split_index = std::string(argv[1]).find("_86");
	if(split_index == -1){
		std::cout<<"The container id is not started with _86"<<std::endl;
		return -1;
	}
	std::string container_id = std::string(argv[1]).substr(split_index+1,15);

  VideoCapture capture(argv[1]);
  namedWindow("Container Video");
  double fps=capture.get(CV_CAP_PROP_FPS); //获取视频帧率
	double pauseTime=1000/fps; //两幅画面中间间隔

	bool container_exist = false;
	ifstream in;
	in.open("./container_roi.txt",ios::in);
	char line[128];
	std::vector<std::string> line_vector;
	std::vector<std::vector<std::string>> line_splited_vector;
	int X = 215;
	int Y = 150;
	while(in.getline(line,sizeof(line)))		//行分隔符可以显示指定，比如按照分号分隔getline(infile,s,';')
	{ 
		line_vector.push_back(line);
		vector<string> lineSplited = split_str(line, " ");
		line_splited_vector.push_back(lineSplited);
		if(lineSplited[0] == container_id){
			cout<<"The container has already existed"<<endl;
			container_exist = true;
			if(lineSplited.size()>2){
				X = atoi(lineSplited[1].c_str());
				Y = atoi(lineSplited[2].c_str());
			}
		}
	}
	in.close();


	setMouseCallback("Container Video",onMouse);
  while (1)
	{
		//读取当前帧
		capture.read(image);
		//播放完退出或者esc退出
		if (image.empty() || waitKey(pauseTime/2)==27) {
			//如果按下过鼠标左键，则进行保存ROI配置，前提是文件中没有该货柜的配置
			if(flag){
				ofstream out;
				if(container_exist == false)
					out.open("./container_roi.txt",ios::in | ios::out | ios::binary | ios::app);
				else
					out.open("./container_roi.txt",ios::out);
				if(out.is_open())
				{
					cout<<"Opening container_roi file is OK"<<endl; 
					if(container_exist == false){
						//不存在该货柜，就直接追加写入ROI配置
						out<<container_id<<" "<<originalPoint.x<<" "<<originalPoint.y<<"\n";
						cout<<container_id<<" "<<originalPoint.x<<" "<<originalPoint.y<<endl;
					}else{
						//存在该货柜就把之间文件中该行删掉，重新写入
						for(int i=0; i<line_vector.size(); i++){
							int index = line_vector[i].find(container_id);
							if(index != -1){
								line_vector.erase(line_vector.begin()+i);
								stringstream ss;
      					ss << container_id<<" "<<originalPoint.x<<" "<<originalPoint.y<<"\n";
								line_vector.push_back(ss.str());
								break;
							}
						}
						//重写覆盖文件
						for(int i=0; i<line_vector.size(); i++){
							out<<line_vector[i];
						}
					}
					out.close();
				}else{
					std::cout<<"File open failed"<<std::endl;
				}

			}
			printf("播放完成\n");
			break;
		}
		//按下鼠标左键，就会标出该点为左上角的80*80的框
		if(flag)
		{
			rectangle(image,originalPoint,Point(originalPoint.x+80, originalPoint.y+80),Scalar(255,0,0),1);
      stringstream ss;
      ss << "originP:" << originalPoint.x << " " << originalPoint.y;
      putText(image,ss.str(),Point(originalPoint.x, originalPoint.y-5),FONT_HERSHEY_SIMPLEX,0.4,Scalar(0,0,255),1,8);
      // ss.clear();
			// ss.str("");
      // ss << "endP:" << processPoint.x << " " << processPoint.y;
      // putText(image,ss.str(),Point(originalPoint.x, originalPoint.y+10),FONT_HERSHEY_SIMPLEX,0.4,Scalar(0,0,255),1,8);
		}

		
		rectangle(image,Point(X, Y),Point(X+80, Y+80),Scalar(0,255,0),1);

		//显示当前视频
		imshow("Container Video",image);

	}


  return 0;
}