#include <cv.h>
#include <highgui.h>
#include <iostream>
using namespace cv;

int main()
{
	Mat img = imread("t1.png");
	Mat img_gray;
	Mat img_tmp;
	
	
	cvtColor(img, img_gray, CV_BGR2GRAY);
	
	namedWindow("T1", 0);
	namedWindow("T2", 0);
	imshow("T1", img_gray);
	int min = 0;
	int max = 70;
	
	inRange(img_gray, Scalar(min), Scalar(max), img_tmp);
	bitwise_not(img_tmp, img_tmp);
	imshow("T2", img_tmp);
	
	waitKey(0);
	return 0;
}
