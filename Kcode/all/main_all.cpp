#include <opencv2/opencv.hpp>
#include "final_fromCAM.h"
#include "final_fromfile.h"
#include "functionEntrances.h"

using namespace cv;

const char* WindName_local = "local";
const char* WindName_filtered = "filtered";

int main(int argc,  char ** argv)
{

	// fromFile(argv[0], argv[1]);
	// string in = "/Users/jinyi/Documents/code/SE/data/eyeDetection.avi";
	// srting out = "/Users/jinyi/Documents/code/SE/data/t1.avi";
	// fromFile(in.c_str(), out.c_str());
	fromCAM();
	return 0;
}


