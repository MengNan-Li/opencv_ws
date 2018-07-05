#include <opencv2/opencv.hpp>
#include <time.h>
#include <iostream>
#include <map>
using namespace std;
using namespace cv;
int main(int argc, char **argv) {
  FileStorage fs("../resource/test.yaml", FileStorage::WRITE);
  //开始文件写入
  fs << "frameCount" << 5;
  //存储vector用[]
  fs << "features" << "[";
  for (int i = 0; i < 3; i++) {
    int x = rand() % 640;
    fs << x;
  }
  fs << "]";
	fs << "map";
  fs << "{" << "one" << 111 << "}"; //存储Map用{}
	fs.release();
	printf("文件写入完毕 \n");

	/*读文件*/
	FileStorage fs2("../resource/test.yaml", FileStorage::READ);
	int frameCount = (int)fs2["frameCount"];
	cout << "frameCount:" << frameCount << endl;	
	FileNode n = fs2["features"];
	FileNodeIterator it = n.begin(), it_end = n.end();
	cout<<"features:";
	int i;
	for(; it != it_end; it++){
		*it >> i;
		cout << i <<" ";
	}
	cout << endl;
	// std::map<string, map<string, int> > map;
	fs2["map"]["one"] >> i;
	cout << "map:" << i << endl;

	return 0;
}