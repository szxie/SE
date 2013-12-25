#include <cv.h>
#include <highgui.h>
#include <iostream>
#include <vector>
using namespace cv;
int maxV=75;
int minV=0;
int max2=255;
int min2=0;
int max3=255;
int min3=0;

void Contours(const Mat &img, Mat &img_re)
{
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	
	findContours(img, contours, hierarchy, CV_RETR_CCOMP , CV_CHAIN_APPROX_SIMPLE);
	
	img_re = img.clone();
	//drawContours(img_re, contours, 0, Scalar(255), CV_FILLED);
	
    int idx = 0;
    for( ; idx >= 0; idx = hierarchy[idx][0] )
    {
        Scalar color( rand()&255, rand()&255, rand()&255 );
        drawContours( img_re, contours, idx, color, 1, 8, hierarchy );
    }
}

void Binary(const Mat &img, Mat &img_re)
{
	Mat img_gray = img.clone();
	Mat img_tmp;
	//cvtColor(img, img_gray, CV_BGR2GRAY);
	
	inRange(img_gray, Scalar(minV,min2,min3), Scalar(maxV,max2,max3), img_tmp);
	bitwise_not(img_tmp, img_tmp);
	img.copyTo(img_re,img_tmp);
	//bitwise_not(img_re, img_re);
	//Contours(img_re, img_re);
}




/*
int main(int argc, const char** argv)
{
	Mat img;
	//img = imread(argv[1], 1);
	Mat img_re;
	
	namedWindow("T1", 0);
	createTrackbar("B1", "T1",&minV, 256);
	createTrackbar("B2", "T1",&maxV, 256);
	
	VideoCapture capture(0);
	
	if (!capture.isOpened())
		std::cout <<"fail\n";
	
	
	while (true) {
		if(!capture.read(img))
		{ std::cout <<"fail\n"; return -1; }
		
		Binary(img, img_re);
		imshow("T1", img_re);
		int c = waitKey(80);
		if((char)c==27 ) break;
	}

	return 0;
}
*/
