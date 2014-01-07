#include "stdafx.h"
using namespace cv;

void averagePoint(const Mat& img_in, const Mat& img_draw, Mat& img_re, int &x, int &y,double ratio=5.5)
{
	/*x = -1;
	return;*/
	int sum;
	//std::cout << "aver " << img_in.step[1] << '\n';
	uchar *imgData =(uchar*) img_in.data;
	x=y=0;
	//std::cout << img_in.rows << " " << img_in.cols << '\n';
	Mat img_tmpr = img_in.clone();
	uchar *imgData_tmpr = (uchar*)img_tmpr.data;

	//namedWindow("TTK3", 0);
	//imshow("TTK3", img_tmpr);
	
	bool *col_f = new bool[img_in.cols];
	for (int i=0; i<img_in.cols; i++) col_f[i] = false;
	
	int col_count = 0;
	int max;
	// max = img_in.rows/ratio;
	
	int tmp = 0;
	int *col_num = new int[img_in.cols];
	
	for (int n=0; n<img_in.cols; n++) {
		col_num[n] = 0;
		for (int m=0; m<img_in.rows; m++) {
			int slot = m*img_in.cols+n;
			if ((int)imgData[slot]==0) {
				col_num[n]++;
			}
		}
		if (col_num[n] > tmp && col_num[n] < img_in.rows) tmp = col_num[n];
	}
	
	max = tmp/ratio;
	//std::cout << "max "<< max << '\n';
	//max = 0;
	
	for (int n=0; n<img_in.cols; n++) {
		if (col_num[n]>max && col_num[n] < img_in.rows) col_f[n] = true;
	}
		
	//for (int i=0; i<img_in.cols; i++) col_f[i] = true;
	
	for (int n=0; n<img_in.cols; n++) {
		for (int m=0; m<img_in.rows; m++) {
			int slot = m*img_in.step[0]+n*img_in.step[1];

			if (col_f[n]) {
				if ((int)imgData[slot] == 0) {
					if (m==0 || m==img_in.rows-1) {
						imgData_tmpr[slot] = 255;
					}
					else {
						x += n;
						y += m;
					}
				}
			}
			else {
				imgData_tmpr[slot]=255;
			}
		}
	
	}
		

	sum = img_tmpr.rows*img_tmpr.cols-countNonZero(img_tmpr);
	img_re = img_draw.clone();
	if (sum == 0) { 
	//std::cout <<"error div o!\n"; 
	x=-1;
	return;}
	x = x / sum;
	y = y / sum;
	
	Point ce(x, y);
	circle(img_re, ce, 3, Scalar(0,255,0));
	
	// namedWindow("TTK1", 0);
	// imshow("TTK1", img_tmpr);
	// namedWindow("TTK2", 0);
	// imshow("TTK2", img_re);
	// waitKey();
	

}

void Contours(const Mat &img, Mat &img_re)
{
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	
	Mat img_tmp = img.clone();
	
	bitwise_not(img_tmp, img_tmp);
	
	// namedWindow("T3", 0);
	// imshow("T3", img_tmp);
	
	findContours(img_tmp, contours, hierarchy, CV_RETR_CCOMP , CV_CHAIN_APPROX_SIMPLE);
	
	// std:: cout << "contours: "<< contours.size() << std:: endl;
	
	img_re = img_tmp.clone();
	//drawContours(img_re, contours, 0, Scalar(255), CV_FILLED);
	
    int idx = -1;
    int num = 0;
    
    std::stringstream ss;
    
    double tmp=0;
    int id = 0;
    for( ; idx >= 0; idx = hierarchy[idx][0] )
    {
    	num++;
        Scalar color( rand()&255, rand()&255, rand()&255 );

       // std::cout << idx << " " << fabs(contourArea(contours[idx])) << std::endl;
        
        double size = fabs(contourArea(contours[idx]));
        if (size > tmp) {
        	tmp = size;
        	id = idx;
        }
        
        
        // drawContours( img_re, contours, idx, color, 1, 8, hierarchy );    	
    }
   	if (id != -1)
   		drawContours(img_re, contours, id, Scalar(255,255,255), CV_FILLED, 8, hierarchy);
    
    

}

