// getMatchedRect: Getting the two new rectangles that had matched.
//
//cv::Mat_<double>  M_rectG: input all rectangle [x,y,w,h]  of one image that from Ground Truth.txt
//cv::Mat_<double>  M_rectR: input all rectangle [x,y,w,h,p] of one image that from result.txt
//						   Note: this M_rectR includes the 'p'


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

cv::Mat_<double>  getImageMatchDegree(cv::Mat_<double> M_rectG,cv::Mat_<double> M_rectR);
vector<double> getMaxIdx(Mat_<double> imageMatchDegree,vector<int> S_rows,vector<int> &outIndex);
void printVector(vector<double> v);

void getMatchedRect(Mat &M_rectG,Mat &M_rectR)
{

	
	Mat_<double> matchedM_rectG;
	Mat_<double> matchedM_rectR;

	if(!M_rectG.empty() && !M_rectR.empty())// If M_rectG isn't empty and M_rectR isn't empty
	{
		Mat imageMatchDegree=getImageMatchDegree(M_rectG,M_rectR.colRange(0,4));
		//Mat imageMatchDegree=getImageMatchDegree(M_rectG, M_rectR);


		vector<int> S_rows;
		for(int i=0;i<imageMatchDegree.rows;i++) S_rows.push_back(i);
		vector<int> outIndex;
		vector<double> V_maxVal;
		int TP_temp=0;
		V_maxVal=getMaxIdx(imageMatchDegree,S_rows,outIndex);
		cout<<"max value:"<<endl;printVector(V_maxVal);cout<<""<<endl;
		for (int k=0;k<V_maxVal.size();k++)
		{
			if (V_maxVal.at(k)>=matchThreshold) 
				{
					matchedM_rectG.push_back<double>(M_rectG.row(k));
					matchedM_rectR.push_back<double>(M_rectR.row(outIndex.at(k)));
					cout<<"\nThe "<<k<<"-th of M_rectG is matched the "<<outIndex.at(k)<<"-th of M_rectR\n"<<endl;
				}
		}		

	}

	M_rectG=matchedM_rectG;
	M_rectR=matchedM_rectR;
	//cout<<M_rectG<<endl;
	//cout<<M_rectR<<endl;

}
