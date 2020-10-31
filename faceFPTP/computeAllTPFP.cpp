/* computeAllTPFP:Compute the True Positive and False Positive during all the threshold

	vector<int>  indexGroundTruth;//a vector of number of [x y w h] in one image that from the "Ground Truth.txt"
	vector<int>  indexResult;//a vector of number of [x y w h] in one image that from the "result.txt"
	Mat_<double>  dataGroundTruth=getDataGround(indexGroundTruth);//a matrix of [x y w h] of all the image
	Mat_<double>  dataResult=getDataResult(indexResult);//a matrix of [x y w h] of all the image

*/
#include "cv.h"
#include "cxcore.h"
#include "highgui.h"
#include "plot.h"
#include "extern_definition.h"

#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <cstdlib>

using namespace std;
using namespace cv;  


void createNewData(Mat_<double> &M_rectG,Mat_<double> &M_rectR);
void printVector(vector<double> v);

//getTPFP function: compute the TP and FP of two image in all the threshold
Mat_<int>  getTPFP(Mat_<double> M_rectG,Mat_<double> M_rectR,vector<double> threshold);
void writeOutput(Mat_<int> M_TPFP,vector<double> threshold);//Write the "FP" , "TP" and "threshold" in the output.txt


void computeAllTPFP(Mat_<double>  dataGroundTruth,vector<int>  indexGroundTruth,Mat_<double>  dataResult,vector<int>  indexResult)
{

	vector<double> threshold;
	cout<<"[x y w h] in the Ground Truth.txt:\n"<<dataGroundTruth<<endl;
	cout<<"\n[x y w h p] in the result.txt:\n"<<dataResult<<endl;

	for(int i=0;i<dataResult.rows;i++) threshold.push_back(dataResult.col(COL_Result-1).at<double>(i));
	sort(threshold.begin(), threshold.end());//Get all the threshold form the 'p' of dataResult
	vector<double>::iterator pos;
	pos = unique(threshold.begin(), threshold.end());
	threshold.erase( pos,threshold.end());// Erase the identical element 

    cout<<"\nThe threshold is:"<<endl;printVector(threshold);cout<<""<<endl;

	Mat M_TPFP=Mat_<int>(threshold.size(), 2);
	M_TPFP=0;
	int sum_indexGroundTruth=0;
	int sum_indexResult=0;
	int pre_sum_indexGroundTruth=0;
	int pre_sum_indexResult=0;

	for(int i=0;i<indexGroundTruth.size();i++)
	{
		cout<<"==================Computing the FP and TP of "<<i+1<<"-th image in all threshold====================\n"<<endl;
		Mat_<int> M_TPFP_temp;
		sum_indexGroundTruth=pre_sum_indexGroundTruth+indexGroundTruth.at(i);
		sum_indexResult=pre_sum_indexResult+indexResult.at(i);
		Mat M_rectG = dataGroundTruth( Range(pre_sum_indexGroundTruth, sum_indexGroundTruth),Range::all());//all rectangle [x,y,w,h]  of one image that from Ground Truth.txt
		Mat M_rectR = dataResult( Range(pre_sum_indexResult, sum_indexResult),Range::all());//all rectangle [x,y,w,h,p]  of one image that from result.txt
		
		cout<<"[x y w h] of that image in the Ground Truth.txt :\n"<<M_rectG<<endl;
		cout<<"[x y w h p] of that image in the result.txt:\n"<<M_rectR<<endl;
		M_TPFP_temp=getTPFP(M_rectG,M_rectR,threshold);//get the TP and FP of two image in all the threshold

		M_TPFP=M_TPFP+M_TPFP_temp;
		cout<<"TP,FP in that image:\n"<<M_TPFP_temp<<endl;
		cout<<"TP,FP in all the image:\n"<<M_TPFP<<endl;
		pre_sum_indexGroundTruth=sum_indexGroundTruth;
		pre_sum_indexResult=sum_indexResult;
		cout<<"==================The FP and TP of "<<i+1<<"-th image in all threshold compute completely.===========\n\n"<<endl;
	}

	writeOutput(M_TPFP,threshold);

	const int Cnt = 10000;
    double X[Cnt] = {0};
    double Y[Cnt] = {0};

    for(int i = 0; i < M_TPFP.rows; i++)
    {
        X[i] = (double)M_TPFP.col(1).at<int>(i);// FP : is X axis
        Y[i] = (double)M_TPFP.col(0).at<int>(i);// TP : is Y axis 
		//cout<<X[i]<<" "<<Y[i]<<endl;
		//X[i] = (double)i;
        //Y[i] = (double)4*i - 20;
    }
	
    cvNamedWindow("faceFPTP(FP is X axis;TP is Y axis)",1);
    Plot plot;
    CvScalar color = CV_RGB(255, 0, 0);
    plot.plot(X, Y, Cnt, color);
    cvShowImage("faceFPTP(FP is X axis;TP is Y axis)", plot.Figure);
    cvWaitKey(0);
	plot.clear();

}