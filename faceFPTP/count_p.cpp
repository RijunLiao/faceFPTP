//count_p: Compute the number of "p>=threshold_temp" and it's index


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

int count_p(vector<double> p,double threshold_temp,vector<int> &index) // Compute the number of "p>=threshold_temp" and it's index
{
	int count=0;
	for(int i=0;i<p.size();i++) if(p.at(i)>=threshold_temp) {count++;index.push_back(i);}

	return count;
}
