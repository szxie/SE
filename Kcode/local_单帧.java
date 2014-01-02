#include "stdafx.h"
#include "Edge.h"
#include "HSV.h"
#include "Circle.h"
#include "Avg.h"

using namespace cv;
void Contours(const Mat &img, Mat &img_re);

const char WindName_local[] = "local";
const char WindName_filtered[] = "filtered";
const char* InputVideoPath = "C:\\Users\\k\\Documents\\Visual Studio 2010\\Projects\\test3\\Debug\\evaluation.avi";
extern double Local_xMin;
extern double Local_xMax;
extern double Local_yMin;
extern double Local_yMax;
const int wastedFrameCnt = 0;

extern int MinH;
extern int MinS;
extern int MinV;
extern int MaxH;
extern int MaxS;
extern int MaxV;

int main()
{
 	Mat frame, binary;
	int count = 1;
	namedWindow( WindName_local, 0 );
	namedWindow( WindName_filtered, 0 );
	VideoCapture reader(InputVideoPath);

    while( reader.read(frame) ) {
		//imshow(WindName, frame);
		bool flag = 1;
		
		if(count<wastedFrameCnt){
			continue;
		}
		Size sizeFrame = frame.size();
		Range colRange(sizeFrame.width*Local_xMin, sizeFrame.width*Local_xMax);
		Range rowRange(sizeFrame.height*Local_yMin, sizeFrame.height*Local_yMax);
		Mat local(frame,rowRange,colRange);
		imshow(WindName_local, local);

		while(1){
			Mat filtered;
			HSV(local,local,filtered);

			inRange(filtered, Scalar(MinH,MinS,MinV), Scalar(MaxH,MaxS,MaxV), binary);
			int nonZeroCount = countNonZero(binary);
			int x,y;
			bitwise_not(binary,binary);
			averagePoint(binary,filtered,filtered,x,y);
			//Circle(filtered,filtered,filtered,x,y);
			if(x==-1){
				flag = 0;
			}
			else{
				flag = 1;
			}
			
			//Circle(filtered,frame,frame,x,y);

			imshow(WindName_filtered, filtered);
			
			char c=cvWaitKey(10);
			if(c=='a'||c=='A')
				break;
			if(c==27)
				return 0;
		}
		if(flag){
			++count;
		}
		std::cout<<count<<std::endl;
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


