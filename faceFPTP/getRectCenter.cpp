// getRectCenter: Getting the centre of rectangle


#include "cv.h"
#include "cxcore.h"
#include "highgui.h"
#include "extern_definition.h"

#include <vector>
#include <iterator>
#include <algorithm>
#include <cstdlib>
using namespace std;
using namespace cv;


Mat getRectCenter(Mat_<double> src)
{
	Mat center;
	Mat start_point=src(Range::all(),Range(0,2));
	Mat end_point=src(Range::all(),Range(0,2))+src(Range::all(),Range(2,4));
	//cout<<"start_point:\n"<<start_point<<endl;
	//cout<<"end_point:\n"<<end_point<<endl;

	center=(start_point+end_point)/2;
	//cout<<"center:\n"<<center<<endl;
	return center;

}