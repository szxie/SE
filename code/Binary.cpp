#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <sstream>
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
	
	Mat img_tmp = img.clone();
	bitwise_not(img_tmp, img_tmp);
	
	namedWindow("T3", 0);
	imshow("T3", img_tmp);
	
	findContours(img_tmp, contours, hierarchy, CV_RETR_CCOMP , CV_CHAIN_APPROX_SIMPLE);
	
	std:: cout << "contours: "<< contours.size() << std:: endl;
	
	img_re = img_tmp.clone();
	//drawContours(img_re, contours, 0, Scalar(255), CV_FILLED);
	
    int idx = 0;
    int num = 0;
    
    std::stringstream ss;
    
    double tmp=0;
    int id = 0;
    for( ; idx >= 0; idx = hierarchy[idx][0] )
    //for (; idx <contours.size(); idx++)
    {
    	num++;
        Scalar color( rand()&255, rand()&255, rand()&255 );

       // std::cout << idx << " " << fabs(contourArea(contours[idx])) << std::endl;
        
        double size = fabs(contourArea(contours[idx]));
        if (size > tmp) {
        	tmp = size;
        	id = idx;
        }
        
        
        drawContours( img_re, contours, idx, color, 1, 8, hierarchy );
        ss << idx;
        string s0 = ss.str();
        
        Mat img_k = img_tmp.clone();
        string s = s0.c_str();
        namedWindow(s, 0);
        drawContours( img_k, contours, idx, color, 1, 8, hierarchy );
    	imshow(s, img_k);
    	imwrite(s+".jpg", img_k);
    	
    }
   // drawContours(img_re, contours, id, Scalar(255,255,255), CV_FILLED, 8, hierarchy);
    
    std::cout << num << std::endl;
    

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
