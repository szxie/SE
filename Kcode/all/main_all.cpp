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
	fromCAM();
	return 0;
}


