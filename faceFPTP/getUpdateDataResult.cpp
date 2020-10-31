/* getUpdateDataResult: Update the W ,H and center of dataResult

//	vector<int>  indexGroundTruth;//a vector of number of [x y w h] in one image that from the "Ground Truth.txt"
//	vector<int>  indexResult;//a vector of number of [x y w h] in one image that from the "result.txt"
//	Mat_<double>  dataGroundTruth=getDataGround(indexGroundTruth);//a matrix of [x y w h] of all the image
//	Mat_<double>  dataResult=getDataResult(indexResult);//a matrix of [x y w h] of all the image

//cv::Mat_<double>  M_rectG: input all rectangle [x,y,w,h]  of one image that from Ground Truth.txt
//cv::Mat_<double>  M_rectR: input all rectangle [x,y,w,h,p] of one image that from result.txt
					   Note: this M_rectR includes the 'p'
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

#define mean_percent 0.5 //The percentage of computing the mean_W and mean_H 

// getMatchedData: Getting the new dataGroundTruth and  dataResult that had matched.
void getMatchedData(Mat_<double>  &dataGroundTruth,vector<int>  indexGroundTruth,Mat_<double>  &dataResult,vector<int>  indexResult,vector<int>  &new_index);
void sortSpecified(Mat src, Mat &dst, int flags,int specified);
Mat getRectCenter(Mat_<double> src);


Mat getUpdateDataResult(Mat_<double>  dataGroundTruth,vector<int>  indexGroundTruth,Mat_<double> dataResult,vector<int>  indexResult)
{
	// getMatchedData: Getting the new dataGroundTruth and  dataResult that had matched.
	Mat_<double> matchedDataGroundTruth;
	Mat_<double> matchedDataResult;
	Mat updateDataResult=dataResult;
	vector<int>  new_index;

	matchedDataGroundTruth=dataGroundTruth;
	matchedDataResult=dataResult;
	//Step 1:getMatchedData
	cout<<"\n\nStep 1:getMatchedData:\n"<<endl;
	getMatchedData(matchedDataGroundTruth,indexGroundTruth,matchedDataResult,indexResult,new_index);

	cout<<"matchedDataGroundTruth:\n"<<matchedDataGroundTruth<<endl;
	cout<<"matchedDataResult:\n"<<matchedDataResult<<endl;
	
	//Step 2: sort matched data by p
	cout<<"\n\nStep 2: sort matched data by p:\n"<<endl;
	Mat all_data=Mat_<double>(matchedDataGroundTruth.rows, COL_Ground+COL_Result);
	matchedDataGroundTruth.copyTo(all_data(Range::all(),Range(0,4)));
	matchedDataResult.copyTo(all_data(Range::all(),Range(4,9)));
	cout<<all_data<<endl;
	sortSpecified(all_data, all_data,1,all_data.cols-1);
	all_data(Range::all(),Range(0,4)).copyTo(matchedDataGroundTruth);
	all_data(Range::all(),Range(4,9)).copyTo(matchedDataResult);
	cout<<"Sorted matchedDataGroundTruth:\n"<<matchedDataGroundTruth<<endl;
	cout<<"Sorted matchedDataResult:\n"<<matchedDataResult<<endl;



	//Step 3:Compute the mean_W and mean_H of 50% matchedDataResult and matchedDataGroundTruth
	cout<<"\n\nStep 3:Compute the mean_W and mean_H of 50% matchedDataResult and matchedDataGroundTruth:\n"<<endl;
	Mat percent_matchedDataResult=matchedDataResult(Range(0,cvRound(matchedDataResult.rows*mean_percent)),Range::all());
	//cout<<cvRound(2.5001)<<endl;

	Mat percent_matchedDataGroundTruth=matchedDataGroundTruth(Range(0,cvRound(matchedDataGroundTruth.rows*mean_percent)),Range::all());
	cout<<"percent_matchedDataResult:\n"<<percent_matchedDataResult<<endl;
	cout<<"percent_matchedDataGroundTruth:\n"<<percent_matchedDataGroundTruth<<endl;
	double mean_W=mean(percent_matchedDataResult.col(2)/percent_matchedDataGroundTruth.col(2))(0);
	cout<<"mean_W:\n"<<mean_W<<endl;
	double mean_H=mean(percent_matchedDataResult.col(3)/percent_matchedDataGroundTruth.col(3))(0);
	cout<<"mean_H:\n"<<mean_H<<endl;


	//Step 4:Update the W and H of percent_matchedDataResult(preserve the conter constant)
	//Constant center
	percent_matchedDataResult.col(0)=percent_matchedDataResult.col(0)+(percent_matchedDataResult.col(2)-percent_matchedDataResult.col(2)/mean_W)/2;//x
	percent_matchedDataResult.col(1)=percent_matchedDataResult.col(1)+(percent_matchedDataResult.col(3)-percent_matchedDataResult.col(3)/mean_H)/2;//y

	cout<<"\n\nStep 4:Update the W and H of percent_matchedDataResult(preserve the conter constant):\n"<<endl;
	percent_matchedDataResult.col(2)=percent_matchedDataResult.col(2)/mean_W;//W
	percent_matchedDataResult.col(3)=percent_matchedDataResult.col(3)/mean_H;//H
	cout<<"Updated percent_matchedDataResult:\n"<<percent_matchedDataResult<<endl;
	

	
	
	//Step 5:Get the rectangle center of percent_matchedDataResult and percent_matchedDataGroundTruth
	cout<<"\n\nStep 5:Get the rectangle center of percent_matchedDataResult and percent_matchedDataGroundTruth:\n"<<endl;
	Mat centerMatchedDataGroundTruth=getRectCenter(percent_matchedDataGroundTruth);
	cout<<"centerMatchedDataGroundTruth [x y]:\n"<<centerMatchedDataGroundTruth<<endl;
	Mat centerMatchedDataResult=getRectCenter(percent_matchedDataResult);
	cout<<"centerMatchedDataResult [x y]:\n"<<centerMatchedDataResult<<endl;

	//Step 6: Compute the mean_delta_y and mean_delta_x between centerMatchedDataGroundTruth and centerMatchedDataResult
	cout<<"\n\nStep 6: Compute the delta_y and delta_x between centerMatchedDataGroundTruth and centerMatchedDataResult:\n"<<endl;
	Mat delta=(centerMatchedDataResult-centerMatchedDataGroundTruth)/percent_matchedDataResult.colRange(2,4);
	cout<<"delta:\n"<<delta<<endl;
	double mean_delta_x=mean(delta.col(0))(0);
	double mean_delta_y=mean(delta.col(1))(0);
	cout<<"mean_delta_x:\n"<<mean_delta_x<<endl;
	cout<<"mean_delta_y:\n"<<mean_delta_y<<endl;

	//Step 7: Update the all dataResult
	cout<<"Update the all dataResult:\n"<<endl;
	updateDataResult.col(2)=updateDataResult.col(2)/mean_W;//R.W
	updateDataResult.col(3)=updateDataResult.col(3)/mean_H;//R.H

	updateDataResult.col(0)=updateDataResult.col(0)-mean_delta_x*updateDataResult.col(2);//R.center.x
	updateDataResult.col(1)=updateDataResult.col(1)-mean_delta_x*updateDataResult.col(3);//R.center.y

	//Round
	for(int i=0;i<updateDataResult.rows;i++)
	{
		for(int j=0;j<updateDataResult.cols-1;j++)
		{
		updateDataResult.col(j).at<double>(i)=cvRound(updateDataResult.col(j).at<double>(i));
		}
	}
	
	return updateDataResult;
}