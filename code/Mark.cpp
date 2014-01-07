 #include 
using namespace cv;

 while( reader.read(frame) ) {
		//imshow(WindName, frame);
		++count;
		if(count<wastedFrameCnt){
			continue;
		}
		if(count%10 == 0){
		Size sizeFrame = frame.size();
		Range colRange(sizeFrame.width*Local_xMin, sizeFrame.width*Local_xMax);
		Range rowRange(sizeFrame.height*Local_yMin, sizeFrame.height*Local_yMax);
		Mat local(frame,rowRange,colRange);
		imshow(WindName_local, local);
		cvSetMouseCallback( WindName_local, on_mouse, 0 );
		//writer<<frame;
      	char c=cvWaitKey(1000/24);
		while(1){
			Mat filtered;
			HSV(local,local,filtered);
			//Contours(filtered,filtered);
			//Circle(filtered,filtered,filtered);
			find_corner(filtered,local);
			imshow(WindName_filtered, local);
			
			char c=cvWaitKey(10);
			if(c==97){
				break;
			}
			if(c==27)
				return 0;
		}
		}
  	}
