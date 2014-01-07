#include <opencv2/opencv.hpp>
#include "Edge.h"
#include "HSV.h"
#include "Circle.h"
#include "Avg.h"
#include "corner.h"

using namespace cv;

extern char* WindName_local;
extern char* WindName_filtered;
const char* OutputVideoPath = "../data/demo.avi";
extern double Local_xMin;
extern double Local_xMax;
extern double Local_yMin;
extern double Local_yMax;

extern int MinH;
extern int MinS;
extern int MinV;
extern int MaxH;
extern int MaxS;
extern int MaxV;


int fromCAM()
{
 	Mat frame, binary;
	int count = 0;
	namedWindow( WindName_local, 1 );
	namedWindow( WindName_filtered, 1 );
	namedWindow( "T1", 1);
	namedWindow( "T2", 1);
	
	// VideoCapture reader(InputVideoPath);
	VideoCapture reader(-1);
	reader.read(frame);
	flip(frame, frame, 1);
	// VideoWriter writer(OutputVideoPath, CV_FOURCC('M', 'J', 'P', 'G'), 20, frame.size());

    while( reader.read(frame) ) {
		//imshow(WindName, frame);
		flip(frame, frame, 1);
		++count;
		Mat print = frame.clone();

		//adjust size part!
		Size sizeFrame = frame.size();
		Range colRange(sizeFrame.width*Local_xMin, sizeFrame.width*Local_xMax);
		Range rowRange(sizeFrame.height*Local_yMin, sizeFrame.height*Local_yMax);
		Mat local(frame,rowRange,colRange);
		imshow(WindName_local, local);

		while(1){
			Mat filtered;
			// MaxV = 40;
			HSV(local,local,filtered);
			find_corner(filtered,frame,print);

			// MaxV = 22;
			HSV(local,local,filtered);
			imshow("T1", filtered);

			inRange(filtered, Scalar(MinH,MinS,MinV), Scalar(MaxH,MaxS,MaxV), binary);
			// bitwise_not(binary,binary);
			int nonZeroCount = countNonZero(binary);
			//Circle(filtered,filtered,filtered,nonZeroCount);
			int Avg_x,Avg_y,Hough_x,Hough_y,hybrid_x,hybrid_y;
			
			bitwise_not(binary,binary);
			averagePoint(binary,frame,frame,Avg_x,Avg_y, 10);
			Circle(filtered,frame,frame,Hough_x,Hough_y);
			if(Avg_x==-1 && Hough_x==-1){
				imshow(WindName_filtered, print);
				break;
			}
			if(Avg_x==-1){
				hybrid_x = Hough_x;
				hybrid_y = Hough_y;
			}
			if(Hough_x==-1){
				hybrid_x = Avg_x;
				hybrid_y = Avg_y;
			}
			if(Avg_x!=-1 && Hough_x!=-1){
				hybrid_x = (Hough_x+Avg_x)/2;
				hybrid_y = (Hough_y+Avg_y)/2;
			}

			Point center( hybrid_x+print.size().width*Local_xMin, hybrid_y+print.size().height*Local_yMin);
			circle( print, center, 3, Scalar(0,0,255), -1, 8, 0 );
			imshow(WindName_filtered, print);

			char c=cvWaitKey(5);
			break;
			/*if(c=='a'||c=='A')
				break;
			if(c==27)
				return 0;*/
		}

		// writer<<print;
		char c=cvWaitKey(5);
		if(c==27)
			return 0;
  	}
	return 0;
}



