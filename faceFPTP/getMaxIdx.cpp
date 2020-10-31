//Compute the max value and it's index in each column of specified rows of Matrix

//vector<int> S_rows: specified rows
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

vector<double> getMaxIdx(Mat_<double> imageMatchDegree,vector<int> S_rows,vector<int> &outIndex)
{
	vector<double> V_maxVal;
	vector<double> V_temp;
	double maxVal;
	int maxIdx;

	for(int i=0;i<imageMatchDegree.cols;i++)
	{
		V_temp.clear();
		for(int j=0;j<S_rows.size();j++) V_temp.push_back(imageMatchDegree.col(i).at<double>(S_rows.at(j)));
		//minMaxIdx(V_temp,&minVal,&maxVal,&minIdx,&maxIdx);
		maxVal=*max_element(V_temp.begin(),V_temp.end());
		for(int j=0;j<V_temp.size();j++)if(V_temp.at(j)==maxVal)maxIdx=j;
		//maxIdx=*find(V_temp.begin(),V_temp.end(),maxVal);
		V_maxVal.push_back(maxVal);
		outIndex.push_back(S_rows.at(maxIdx));
	}
	return V_maxVal;
}