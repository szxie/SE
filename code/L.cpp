#include <cv.h>
#include <highgui.h>
#include <iostream>
#include <vector>
#include "Binary.cpp"
using namespace cv;

int main(int argc, const char** argv)
{
	Mat img;
	img = imread(argv[1], 1);
	Mat img_re;
	
	namedWindow("T1", 0);
	namedWindow("T2", 0);
	//VideoCapture capture(0);
	
	//if (!capture.isOpened())
		//std::cout <<"fail\n";
	
	
	//while (true) {
		//if(!capture.read(img))
		//{ std::cout <<"fail\n"; return -1; }
		
		Binary(img, img_re);
		inRange(img_re, Scalar(0), Scalar(100), img_re);
		bitwise_not(img_re, img_re);
		imshow("T1", img_re);
		Contours(img_re, img_re);
		imshow("T2", img_re);
		int c = waitKey();
		
	//}

	return 0;
}
