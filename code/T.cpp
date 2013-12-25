#include <cv.h>
#include <highgui.h>
#include <iostream>
#include <vector>
using namespace cv;

int main(int argc, const char** argv)
{
	Mat img;
	//img = imread(argv[1], 1);
	Mat img_re;
	
	namedWindow("T1", 0);
	//createTrackbar("B1", "T1",&minV, 256);
	//createTrackbar("B2", "T1",&maxV, 256);
	
	VideoCapture capture("../data/v1.avi");
	
	if (!capture.isOpened())
	{	std::cout <<"fail\n";}
	
	
	while (true) {
		if(!capture.read(img))
		{ std::cout <<"fail\n"; return -1; }
		
		//Binary(img, img_re);
		imshow("T1", img_re);
		int c = waitKey(80);
		if((char)c==27 ) break;
	}

	return 0;
}
