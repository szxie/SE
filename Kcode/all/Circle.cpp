#include "stdafx.h"
#include "HSV.h"

using namespace cv;
double Ratio = 0.8;
double Local_xMin = 0.4;
double Local_xMax = 0.6;
double Local_yMin = 0.4;
double Local_yMax = 0.65;
//double MaxfillRate_others = 0.5;
double MinfillRate_others = 0;
double MaxfillRate_circle = 1;
//double MinfillRate_circle = 0.6;

bool goodFillRate(const Mat &img,uchar* data,int center,int radius,double MaxfillRate_others=0.7, double MinfillRate_circle = 0.7);

//依据src1来找圆，输出图依照src2，结果为srcorin
void Circle(const Mat &src1, const Mat &src2, Mat &srcorin, int &x, int &y, double MaxfillRate_others=0.7, double MinfillRate_circle =0.7, double divisor = 2.6)
{
	x = -1;
	//return;
	Mat src_gray;
	srcorin = src2.clone();
    /// Convert it to gray
    
    //src_gray = src1;
    cvtColor( src1, src_gray, CV_BGR2GRAY );

    /// Reduce the noise so we avoid false circle detection
    GaussianBlur( src_gray, src_gray, Size(9, 9), 2, 2 );

    vector<Vec3f> circles;

    /// Apply the Hough Transform to find the circles
  
    HoughCircles( src_gray, circles, CV_HOUGH_GRADIENT, 3, src_gray.rows/10, 100, src_gray.rows/divisor, 0, src_gray.rows/2);
	//HoughCircles( src_gray, circles, CV_HOUGH_GRADIENT, 3, src_gray.rows/5, 100, src_gray.rows, 0, src_gray.rows/2);
    /*for( size_t i = 0; i < circles.size(); i++ )
    {
        std::cout<<cvRound(circles[i][0])<<' '<<cvRound(circles[i][1])<<' '<<cvRound(circles[i][2])<<std::endl;
	}*/
  /// Draw the circles detected
	int total_x = 0;
	int total_y = 0;
	int circleCount = 0;
    for( size_t i = 0; i < circles.size(); i++ )
    {
		Point center(cvRound(circles[i][0]),cvRound(circles[i][1]));
        int radius = cvRound(circles[i][2]);
        // circle center
		int circleSize = radius*radius*3.14;
		if(!goodFillRate(src1,src1.data,center.y*src1.step[0]+center.x*src1.step[1],radius,MaxfillRate_others,MinfillRate_circle)){
			continue;
		}
		Point _center(cvRound(circles[i][0])+src2.size().width*Local_xMin, cvRound(circles[i][1])+src2.size().height*Local_yMin);
        circle( srcorin, center, 3, Scalar(0,255,0), -1, 8, 0 );
		total_x += center.x;
		total_y += center.y;
		++circleCount;
		//return;
        circle( srcorin, center, radius, Scalar(0,0,255), 1, 8, 0 );
    }
	if(circleCount==0){
		return;
	}
	x = total_x/circleCount;
	y = total_y/circleCount;
}


bool goodFillRate(const Mat &img,uchar* data,int center,int radius,double MaxfillRate_others, double MinfillRate_circle){
	int count_circle = 0;
	int count_square = 0;
	double fillRate_circle;
	double fillRate_others;

	for(int i=-radius;i<=radius;++i){
		for(int j=-radius;j<=radius;++j){
			int slot = center+i*img.step[0]+j*img.step[1];
			if(isOutOfBound(slot,img)){
				//std::cout<<"i: "<<i<<"\nj: "<<j<<"\nradius: "<<radius<<"\ncenter: "<<center<<"\nslot: "<<slot<<'\n';
				return 0;
			}
			if(!(data[slot]==255 && data[slot+1]==255 && data[slot+2]==255)){
				++count_square;
				if(i*i+j*j<=radius*radius){
					++count_circle;
				}
			}
		}
	}
	fillRate_others = double(count_square-count_circle)/(radius*radius*(4-3.14159));
	fillRate_circle = double(count_circle)/(radius*radius*3.14159);

	if(fillRate_circle>MaxfillRate_circle || fillRate_circle<MinfillRate_circle || fillRate_others>MaxfillRate_others || fillRate_others<MinfillRate_others){
		return 0;
	}
	//std::cout<<fillRate<<"\n";
	return 1;
}

/*
int main(int argc, const char** argv)
{
	Mat img = imread(argv[1], 1);
	Mat img2 = imread(argv[1], 1);
	Mat img_re;
	Circle(img, img2, img_re);
	
	namedWindow( "TEST", CV_WINDOW_AUTOSIZE );
  	imshow( "TEST", img_re );
  	
  	waitKey(0);
  	return 0;
}
*/
