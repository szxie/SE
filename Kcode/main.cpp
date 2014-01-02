#include "stdafx.h"
#include "Edge.h"
#include "HSV.h"
#include "Circle.h"
#include "Avg.h"
#include "corner.h"

using namespace cv;
void Contours(const Mat &img, Mat &img_re);

const char WindName_local[] = "local";
const char WindName_filtered[] = "filtered";
const char* InputVideoPath = "F:\\eyeDetection_2.avi";
const char* OutputVideoPath = "F:\\demo.avi";
extern double Local_xMin;
extern double Local_xMax;
extern double Local_yMin;
extern double Local_yMax;
const int wastedFrameCnt = 50;

extern int MinH;
extern int MinS;
extern int MinV;
extern int MaxH;
extern int MaxS;
extern int MaxV;

int main()
{
 	Mat frame, binary;
	int count = 0;
	namedWindow( WindName_local, 0 );
	namedWindow( WindName_filtered, 0 );
	VideoCapture reader(InputVideoPath);
	reader.read(frame);
	VideoWriter writer(OutputVideoPath, CV_FOURCC('M', 'J', 'P', 'G'), 20, frame.size());

    while( reader.read(frame) ) {
		//imshow(WindName, frame);
		++count;
		Mat print = frame.clone();
		if(count<wastedFrameCnt){
			continue;
		}
		Size sizeFrame = frame.size();
		Range colRange(sizeFrame.width*Local_xMin, sizeFrame.width*Local_xMax);
		Range rowRange(sizeFrame.height*Local_yMin, sizeFrame.height*Local_yMax);
		Mat local(frame,rowRange,colRange);
		imshow(WindName_local, local);

		bool haha = 1;
		while(1){
			Mat filtered;

			MaxV = 40;
			HSV(local,local,filtered);
			find_corner(filtered,frame,print);

			MaxV = 22;
			HSV(local,local,filtered);
			inRange(filtered, Scalar(MinH,MinS,MinV), Scalar(MaxH,MaxS,MaxV), binary);
			bitwise_not(binary,binary);
			int nonZeroCount = countNonZero(binary);
			//Circle(filtered,filtered,filtered,nonZeroCount);
			int Avg_x,Avg_y,Hough_x,Hough_y,hybrid_x,hybrid_y;
			averagePoint(binary,frame,frame,Avg_x,Avg_y);
			Circle(filtered,frame,frame,Hough_x,Hough_y);
			if(Avg_x==-1 && Hough_x==-1){
				//imshow(WindName_filtered, print);
				haha = 0;
				break;
			}
			haha = 1;
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


			/*if(hybrid_x<local.size().width*6/11){
				Point center( hybrid_x+print.size().width*Local_xMin-2, hybrid_y+print.size().height*Local_yMin);
				circle( print, center, 5, Scalar(0,0,255), -1, 8, 0 );
			}
			else{
				Point center( hybrid_x+print.size().width*Local_xMin+2, hybrid_y+print.size().height*Local_yMin);
				circle( print, center, 5, Scalar(0,0,255), -1, 8, 0 );
			}*/
			Point center( hybrid_x+print.size().width*Local_xMin, hybrid_y+print.size().height*Local_yMin);
			circle( print, center, 5, Scalar(0,0,255), -1, 8, 0 );
			imshow(WindName_filtered, print);

			char c=cvWaitKey(5);
			break;
			/*if(c=='a'||c=='A')
				break;
			if(c==27)
				return 0;*/
		}
		if(haha){
		writer<<print;
		}
		char c=cvWaitKey(5);
		if(c==27)
			return 0;
  	}
	return 0;
}

void Contours(const Mat &img, Mat &img_re)
{
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	
	findContours(img, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
	
	img_re = img.clone();
	//drawContours(img_re, contours, 0, Scalar(255), CV_FILLED);
	
    int idx = 0;
    for( ; idx >= 0; idx = hierarchy[idx] [0] )
    {
        Scalar color( rand()&255, rand()&255, rand()&255 );
        drawContours( img_re, contours, idx, color, 1, 8, hierarchy );
    }
} 


