// getMatchedData: Getting the new dataGroundTruth and  dataResult that had matched.

//	vector<int>  indexGroundTruth;//a vector of number of [x y w h] in one image that from the "Ground Truth.txt"
//	vector<int>  indexResult;//a vector of number of [x y w h] in one image that from the "result.txt"
//	Mat_<double>  dataGroundTruth=getDataGround(indexGroundTruth);//a matrix of [x y w h] of all the image
//	Mat_<double>  dataResult=getDataResult(indexResult);//a matrix of [x y w h] of all the image

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


void getMatchedRect(Mat &M_rectG,Mat &M_rectR);// Getting the two new rectangles that had matched.

void getMatchedData(Mat_<double>  &dataGroundTruth,vector<int>  indexGroundTruth,Mat_<double>  &dataResult,vector<int>  indexResult,vector<int>  &new_index)
{

	Mat_<double> matchedDataGroundTruth;
	Mat_<double> matchedDataResult;

	int sum_indexGroundTruth=0;
	int sum_indexResult=0;
	int pre_sum_indexGroundTruth=0;
	int pre_sum_indexResult=0;

	for(int i=0;i<indexGroundTruth.size();i++)
	{
		cout<<"================== Getting the two new rectangles that had matched in the "<<i+1<<"-th image====================\n"<<endl;
		sum_indexGroundTruth=pre_sum_indexGroundTruth+indexGroundTruth.at(i);
		sum_indexResult=pre_sum_indexResult+indexResult.at(i);
		Mat M_rectG = dataGroundTruth( Range(pre_sum_indexGroundTruth, sum_indexGroundTruth),Range::all());//all rectangle [x,y,w,h]  of one image that from Ground Truth.txt
		Mat M_rectR = dataResult( Range(pre_sum_indexResult, sum_indexResult),Range::all());//all rectangle [x,y,w,h,p]  of one image that from result.txt
		
		cout<<"[x y w h] of that image in the Ground Truth.txt :\n"<<M_rectG<<endl;
		cout<<"[x y w h p] of that image in the result.txt:\n"<<M_rectR<<endl;

		getMatchedRect(M_rectG,M_rectR);// Getting the two new rectangles that had matched.
		matchedDataGroundTruth.push_back<double>(M_rectG);
		matchedDataResult.push_back<double>(M_rectR);
		new_index.push_back(M_rectG.rows);

		cout<<"The matched [x y w h] of that image in the Ground Truth.txt :\n"<<M_rectG<<endl;
		cout<<"The matched [x y w h p] of that image in the result.txt:\n"<<M_rectR<<endl;

		pre_sum_indexGroundTruth=sum_indexGroundTruth;
		pre_sum_indexResult=sum_indexResult;
		cout<<"============== Getting the two new rectangles that had matched in the "<<i+1<<"-th image compute completely.======\n\n"<<endl;
	}

	dataGroundTruth=matchedDataGroundTruth;
	dataResult=matchedDataResult;

	cout<<"The matched dataGroundTruth is :\n"<<dataGroundTruth<<endl;
	cout<<"The matched dataResult is :\n"<<dataResult<<endl;

}
