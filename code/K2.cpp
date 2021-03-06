
#include "HSV.cpp"
using namespace cv;

const char WindName_local[] = "local";
const char WindName_filtered[] = "filteded";
const char* InputVideoPath = "F:\\eyeDetection瞪眼.avi";
const double Local_xMin = 0.45+0.05;
const double Local_xMax = 0.8+0.05;
const double Local_yMin = 0.2+0.05;
const double Local_yMax = 0.55+0.05;
const int wastedFrameCnt = 0;

extern int MaxH;
extern int MinH;
extern int MaxS;
extern int MinS;
extern int MaxV;
extern int MinV;

int main()
{
Mat frame, binary;
int count = 0;
namedWindow( WindName_local, 0 );
namedWindow( WindName_filtered, 0 );
VideoCapture reader(0);

while( reader.read(frame) ) {
//imshow(WindName, frame);



Size sizeFrame = frame.size();
Range colRange(sizeFrame.width*Local_xMin, sizeFrame.width*Local_xMax);
Range rowRange(sizeFrame.height*Local_yMin, sizeFrame.height*Local_yMax);
Mat local(frame,rowRange,colRange);
imshow(WindName_local, local);

while(1){
	Mat filteded;
	HSV(local,local,filteded);
	inRange(filteded, Scalar(MinH,MinS,MinV), Scalar(MaxH,MaxS,MaxV), binary); 

	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	findContours(filteded, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
	Mat contoured = filteded.clone();
//drawContours(img_re, contours, 0, Scalar(255), CV_FILLED);
	int idx = 0;
	for( ; idx >= 0; idx = hierarchy[idx] [0] )
	{
	Scalar color( rand()&255, rand()&255, rand()&255 );
	drawContours( contoured, contours, idx, color, 1, 8, hierarchy );
	} 

//Circle(filteded,filteded,filteded);
	imshow(WindName_filtered, contoured);

char c=cvWaitKey(10);
if(c==97)
break;
if(c==27)
return 0;
}
}
return 0;
}
