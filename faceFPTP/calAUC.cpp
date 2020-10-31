#include "cv.h"
#include "cxcore.h"
#include "highgui.h"

#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <cstdlib>

using namespace std;
using namespace cv; 

double calAUC(const std::vector<double> & dec_values, const Mat& labels){
	double roc = 0;
	size_t size = dec_values.size();
	size_t i;
    vector<size_t> indices(size);
    const unsigned char * pLabels = labels.ptr(0);
    
	for(i = 0; i < size; ++i) indices[i] = i;
    
	std::sort(indices.begin(), indices.end(), Comp( &dec_values[0] ));
}