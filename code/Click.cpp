#include <cv.h>
#include <highgui.h>
#include <iostream>
#include <vector>
#include <sstream>
using namespace cv;

IplImage* src=0;  
void on_mouse( int event, int x, int y, int flags, void* ustc)  
{  
    CvFont font;  
    cvInitFont(&font, CV_FONT_HERSHEY_SIMPLEX, 0.5, 0.5, 0, 1, CV_AA);  
          
    if( event == CV_EVENT_LBUTTONDOWN )  
    {  
        CvPoint pt = cvPoint(x,y);  
        char temp[16];  
        sprintf(temp,"(%d,%d)",pt.x,pt.y); 
        
        std::cout <<pt.x << " " << pt.y << std::endl; 
        
        //cvPutText(src,temp, pt, &font, cvScalar(255, 255, 255, 0));  
        cvCircle( src, pt, 2,cvScalar(0,255,0,0) ,CV_FILLED, CV_AA, 0 );  
        cvShowImage( "src", src );  
    }   
}  
  
int main(int argc, const char** argv)  
{  
    src=cvLoadImage(argv[1],1);  
  
    cvNamedWindow("src",1);  
    cvSetMouseCallback( "src", on_mouse, 0 );  
      
    cvShowImage("src",src);  
    cvWaitKey(0);   
    cvDestroyAllWindows();  
    cvReleaseImage(&src);  
  
    return 0;  
} 
