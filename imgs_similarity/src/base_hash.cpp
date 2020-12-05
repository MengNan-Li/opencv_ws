#include<iostream>

#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;

//直方图计算相似度
double calcHistM(Mat pic1,Mat pic2) {
	//计算相似度
	double dSimilarity;
	if (pic2.channels() == 1) {//单通道时，
		int histSize = 256;
		float range[] = { 0, 256 };
		const float* histRange = { range };
		bool uniform = true;
		bool accumulate = false;

		Mat hist1, hist2;

		calcHist(&pic2, 1, 0, cv::Mat(), hist1, 1, &histSize, &histRange, uniform, accumulate);
		normalize(hist1, hist1, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());

		calcHist(&pic1, 1, 0, cv::Mat(), hist2, 1, &histSize, &histRange, uniform, accumulate);
		normalize(hist2, hist2, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());

		dSimilarity = cv::compareHist(hist1, hist2, CV_COMP_CORREL);//,CV_COMP_CHISQR,CV_COMP_INTERSECT,CV_COMP_BHATTACHARYYA    CV_COMP_CORREL

		//cout << "similarity = " << dSimilarity << endl;
		return dSimilarity;
	}
	else {//三通道时
		cvtColor(pic2, pic2, COLOR_BGR2HSV);
		cvtColor(pic1, pic1, COLOR_BGR2HSV);

		int h_bins = 50, s_bins = 60;
		int histSize[] = { h_bins, s_bins };
		float h_ranges[] = { 0, 180 };
		float s_ranges[] = { 0, 256 };
		const float* ranges[] = { h_ranges, s_ranges };
		int channels[] = { 0, 1 };

		MatND hist1, hist2;

		calcHist(&pic2, 1, channels, cv::Mat(), hist1, 2, histSize, ranges, true, false);
		normalize(hist1, hist1, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());

		calcHist(&pic1, 1, channels, cv::Mat(), hist2, 2, histSize, ranges, true, false);
		normalize(hist2, hist2, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());

		dSimilarity = cv::compareHist(hist1, hist2, CV_COMP_CORREL); //,CV_COMP_CHISQR,CV_COMP_INTERSECT,CV_COMP_BHATTACHARYYA  CV_COMP_CORREL

		//cout << "similarity = " << dSimilarity << endl;
	}
	return dSimilarity;
}

//感知哈希算法相似度
int hashSimilarity(Mat pic1, Mat pic2) {
	Mat matDst1, matDst2;

	resize(pic1, matDst1, Size(8,8), 0, 0, INTER_CUBIC);
	resize(pic2, matDst2, Size(8, 8), 0, 0, INTER_CUBIC);

	cv::cvtColor(matDst1, matDst1, CV_BGR2GRAY);
	cv::cvtColor(matDst2, matDst2, CV_BGR2GRAY);

	int iAvg1 = 0, iAvg2 = 0;
	int arr1[64], arr2[64];

	for (int i = 0; i < 8; i++) {
		uchar* data1 = matDst1.ptr<uchar>(i);
		uchar* data2 = matDst2.ptr<uchar>(i);

		int tmp = i * 8;

		for (int j = 0; j < 8; j++) {
			int tmp1 = tmp + j;

			arr1[tmp1] = data1[j] / 4 * 4;
			arr2[tmp1] = data2[j] / 4 * 4;

			iAvg1 += arr1[tmp1];
			iAvg2 += arr2[tmp1];
		}
	}

	iAvg1 /= 64;
	iAvg2 /= 64;

	for (int i = 0; i < 64; i++) {
		arr1[i] = (arr1[i] >= iAvg1) ? 1 : 0;
		arr2[i] = (arr2[i] >= iAvg2) ? 1 : 0;
	}

	int iDiffNum = 0;

	for (int i = 0; i < 64; i++)
		if (arr1[i] != arr2[i])
			++iDiffNum;

	return iDiffNum;
}

//

int main(int argc, char* argv[])
{
	if (argc < 2) {
		cout << "请输入 图片1 和图片2 的路径，中间空格分开" << endl << endl;
		return 0;
	}
	Mat img1 = imread(argv[1]);//("F:\\shiyandata\\1.jpg");
	Mat img2 = imread(argv[2]);//("F:\\shiyandata\\3.jpg");
	Mat img1_r, img2_r;

  img1 = img1(Range(0,310), Range(180,460));
  img2 = img2(Range(0,310), Range(180,460));
	// resize(img1, img1_r, Size(), 0.3, 0.3, INTER_LINEAR);
	// resize(img2, img2_r, Size(), 0.3, 0.3, INTER_LINEAR);

	namedWindow("1",WINDOW_AUTOSIZE);
	imshow("1", img1);

	namedWindow("2",WINDOW_AUTOSIZE);
	imshow("2", img2);

	double simi_score = calcHistM(img1, img2);
	int hash_score = hashSimilarity(img1, img2);

	cout << "直方图匹配方法:  " << simi_score <<"  ... 小于0.8 ：两张图片存在较大变化，值在0-10 之间"<< endl<<endl;

	cout << "哈希相似度方法: " << hash_score << "  ... 小于等于6 ：两张图片相同，大于等于9：两张图片不同，7-8：两张有轻微变化" << endl;
	//else if (hash_score > 10)
	//	cout << "哈希相似度计算距离:" << hash_score << "... they are two different images!" << endl;
	//else
	//	cout << "哈希相似度计算距离:" << hash_score << "... two image are somewhat similar!" << endl;

	waitKey(0);
	
	system("pause");
	destroyAllWindows();

	return 0;

}
