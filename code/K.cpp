#include <opencv2/opencv.hpp>
#include <iostream>
#include "Binary.cpp"
#include "HSV.cpp"
#include "Circle.cpp"
#include <sstream>
#include "Avg.cpp"
using namespace cv;

const char WindName_local[] = "local";
const char WindName_filtered[] = "filted";
const string InputVideoPath = "../data/eyeDetection.avi";
const double Local_xMin = 0.45;
const double Local_xMax = 0.8;
const double Local_yMin = 0.2;
const double Local_yMax = 0.55;
const int wastedFrameCnt = 0;

extern int MaxH;
extern int MinH;
extern int MaxS;
extern int MinS;
extern int MaxV;
extern int MinV;

int main(int argc, const char** argv)
{
	Mat frame;
	int count = 0;
	namedWindow( WindName_local, CV_WINDOW_NORMAL );
	namedWindow( WindName_filtered, CV_WINDOW_NORMAL );
	namedWindow("Tmp", CV_WINDOW_NORMAL );
	namedWindow("T2", CV_WINDOW_NORMAL );
	namedWindow("T3", CV_WINDOW_NORMAL );
	Mat filted, binary;
	    std::stringstream ss;
	//VideoCapture reader(0);
	//if (!reader.isOpened())
		//std::cout <<"fail\n";
		frame = imread(argv[1], 1);
	//while( reader.read(frame) ) {
	int num=3;
	//while (1){

        num++;
		//frame = imread("../data/k"+s+".png",1);
		//Mat local = frame.clone();
		flip(frame, frame, 1);
		Size sizeFrame = frame.size();

		Range colRange(sizeFrame.width*Local_xMin, sizeFrame.width*Local_xMax);
		Range rowRange(sizeFrame.height*Local_yMin, sizeFrame.height*Local_yMax);
		Mat local(frame,rowRange,colRange);
		
		//local = frame.clone(); 	
		//imshow(WindName_local, local);
		
		
		
		local = imread(argv[1], 1);
		//***********filted->filted
		HSV(local,local,filted);
		imshow("Tmp", filted);
		//*************0/1->binary
		inRange(filted, Scalar(MinH,MinS,MinV), Scalar(MaxH,MaxS,MaxV), binary);
		//	char b=cvWaitKey(10000000);
		//if(b==98)continue; 
		//Circle(binary, local, local);
		
		//*********filled->binary
		Contours(binary,binary);
		//imshow(WindName_filtered, binary);
		Mat img_tmp;
		//********reverse->img_tmp
		//bitwise_not(binary, img_tmp);
		img_tmp = binary.clone();
		imshow("T3", img_tmp);
		//******average point->img_avg
		Mat img_avg;
		int x, y;
		x=y=-1;
		averagePoint(img_tmp, local, img_avg, x, y);
		//averagePoint(img_tmp, img_tmp, img_avg, x, y);
		std::cout << "x " << x << " y " << y << '\n';
		imshow("T2", img_avg);
		//char a=cvWaitKey(10000000);
		//if(a==97)continue;
		
		//******hough circle
		//Circle(binary, local, local);
		//imshow("T2", local);
		frame.release();
		binary.release();
		filted.release();
		char c = waitKey();
		//if(c==27)break;
		//waitKey();
	//}
	//}
	return 0;
}

