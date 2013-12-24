#include <cv.h>
#include <highgui.h>
#include <iostream>
using namespace cv;
int maxV=75;
int minV=0;

void Binary(const Mat &img, Mat &img_re)
{
	Mat img_gray;
	cvtColor(img, img_gray, CV_BGR2GRAY);
	
	inRange(img_gray, Scalar(minV), Scalar(maxV), img_re);
}

int main(int argc, const char** argv)
{
	Mat img = imread(argv[1], 1);
	Mat img_re;
	
	namedWindow("T1", 0);
	createTrackbar("B1", "T1",&minV, 256);
	createTrackbar("B2", "T1",&maxV, 256);
	while (true) {
		Binary(img, img_re);
		imshow("T1", img_re);
		int c = waitKey(80);
		if((char)c==27 ) break;
	}

	return 0;
}
