#include <iostream>
#include<opencv2/opencv.hpp>
#include <opencv2/legacy/legacy.hpp>

using namespace std;
using namespace cv;

int getORB(char * imagePatha,char * imagePathb){
   double t;
   t=getTickCount();
   Mat img_1 = imread(imagePatha);
   Mat img_2 = imread(imagePathb);
   if (!img_1.data || !img_2.data)   
   {
      cout << "error reading images " << endl;      return -1;
   }
   ORB orb;
   vector<KeyPoint> keyPoints_1, keyPoints_2;
   Mat descriptors_1, descriptors_2;
   orb(img_1, Mat(), keyPoints_1, descriptors_1);
   orb(img_2, Mat(), keyPoints_2, descriptors_2);
   BruteForceMatcher<HammingLUT> matcher;
   vector<DMatch> matches;
   matcher.match(descriptors_1, descriptors_2, matches);
   double max_dist = 0; double min_dist = 100;
   for( int i = 0; i < descriptors_1.rows; i++ )   
   {
      double dist = matches[i].distance;
      if( dist < min_dist ) min_dist = dist;
      if( dist > max_dist ) max_dist = dist;
   }
   printf("-- Max dist : %f \n", max_dist );
   printf("-- Min dist : %f \n", min_dist );
   std::vector< DMatch > good_matches;
   for( int i = 0; i < descriptors_1.rows; i++ )   
   {
     if( matches[i].distance < 0.6*max_dist )
	 {
		good_matches.push_back(matches[i]);
     }
   }
	t=getTickCount()-t;
	t=t*1000/getTickFrequency();
	Mat img_matches;
	drawMatches(img_1, keyPoints_1, img_2, keyPoints_2,good_matches, img_matches,
	Scalar::all(-1), Scalar::all(-1),vector<char>(),
	DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
	imshow( "Match", img_matches);   
	printf( "%f ms\n", t );
	cvWaitKey(0);
	return 0;
}

int main()
{
	getORB("/home/lmn/cabinet_imgs/2020-06-04-14-47-24.png","/home/lmn/cabinet_imgs/2020-06-04-14-47-35.png");
	return 0;
}
