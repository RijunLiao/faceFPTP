/* getTPFP function: compute the TP and FP of two image in all the threshold

cv::Mat_<double>  M_rectG: input all rectangle [x,y,w,h]  of one image that from Ground Truth.txt
cv::Mat_<double>  M_rectR: input all rectangle [x,y,w,h,p] of one image that from result.txt
						   Note: this M_rectR includes the 'p'

vector<double> threshold: threshold that determine a rectangle whether or not a face

M_TPFP: (output) the rows of M_TPFP is equal to the rows of threshold
		//the 0-th column of M_TPFP is TP;
		//the 1-th column of M_TPFP is FP;

*/

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
void printVector(vector<double> v);
void printVector(vector<int> v);

int count_p(vector<double> p,double threshold_temp,vector<int> &index);// Compute the number of "p>=threshold_temp" and it's index

//Compute the max value and it's index in each column of specified rows of Matrix
vector<double> getMaxIdx(Mat_<double> imageMatchDegree,vector<int> S_rows,vector<int> &outIndex);


Mat_<int>  getTPFP(Mat_<double> M_rectG,Mat_<double> M_rectR,vector<double> threshold)
{
	int sum_TPFP=0;
	vector<int> TP( threshold.size(), 0 );
	vector<int> FP( threshold.size(), 0 );
	Mat M_TPFP=Mat_<int>(threshold.size(), 2);
	//Mat_<double> M_TPFP;
	Mat_<double> imageMatchDegree;
	double threshold_temp;

	vector<double> p;
	vector<int> index;
	for(int i=0;i<M_rectR.rows;i++) p.push_back(M_rectR.col(4).at<double>(i));// p: the 4-th column of M_rectR
	//printVector(p);

	
	if (M_rectG.empty() && !M_rectR.empty())// If M_rectG is empty and M_rectR isn't empty
	{
			for (int i=0;i<threshold.size();i++)// Compute the FP during all the threshold.
			{									//( TP=0 when M_rectG is empty and M_rectR isn't empty )
				threshold_temp=threshold.at(i);	
				index.clear();
				FP.at(i)=count_p(p,threshold_temp,index);				
			}
	}
	else if(!M_rectG.empty() && !M_rectR.empty())// If M_rectG isn't empty and M_rectR isn't empty
	{
		imageMatchDegree=getImageMatchDegree(M_rectG,M_rectR.colRange(0,4));

		for (int i=0;i<threshold.size();i++)// Compute the FP and TP during all the threshold.
		{
			threshold_temp=threshold.at(i);
			index.clear();
			sum_TPFP=count_p(p,threshold_temp,index);
			cout<<"\nThe index of p>=threshold:"<<threshold_temp<<endl;printVector(index);cout<<""<<endl;
			if (sum_TPFP!=0)
			{
				vector<int> outIndex;
				vector<double> V_maxVal;
				int TP_temp=0;
				V_maxVal=getMaxIdx(imageMatchDegree,index,outIndex);
				cout<<"\nThe max val in each column of p>=threshold :"<<threshold_temp<<endl;printVector(V_maxVal);cout<<""<<endl;
				for (int k=0;k<V_maxVal.size();k++)
				{
					if (V_maxVal.at(k)>=matchThreshold) 
					{
						TP_temp++;
						cout<<"In the threshold:"<<threshold_temp<<"\nThe "<<k<<"-th of M_rectG is matched the "<<outIndex.at(k)<<"-th of M_rectR\n"<<endl;
					}
				}
				TP.at(i)=TP_temp;
				FP.at(i)=sum_TPFP-TP_temp;
			}
		}

	}


	for(int i=0;i<threshold.size();i++) M_TPFP.col(0).at<int>(i)=TP.at(i);
	for(int i=0;i<threshold.size();i++) M_TPFP.col(1).at<int>(i)=FP.at(i);
	//M_TPFP.push_back(TP);
	//M_TPFP.push_back(FP);
	return M_TPFP;
}
