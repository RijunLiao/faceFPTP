/* getImageMatchDegree function: compute the Match Degree of two image

cv::Mat_<double>  M_rectG: input all rectangle [x,y,w,h]  of one image that from Ground Truth.txt
cv::Mat_<double>  M_rectR: input all rectangle [x,y,w,h] of one image that from result.txt
						  Note: this M_rectR does not include the 'p'

MatchDegree: output

*/

#include "cv.h"
#include "cxcore.h"
#include "highgui.h"
#include <vector>
#include <iterator>
#include <algorithm>
#include <cstdlib>
using namespace std;
using namespace cv;

//getMatchDegree function: compute the Match Degree of two rectangle
double getMatchDegree(vector<double> rectG,vector<double> rectR);
void printVector(vector<double> v);
Mat_<double> preprocess(Mat_<double> imageMatchDegree);//retain the max value in each row of imageMatchDegree,other element are zeros.
						

cv::Mat_<double>  getImageMatchDegree(cv::Mat_<double> M_rectG,cv::Mat_<double> M_rectR)
{

	vector<double> rectG;
	vector<double> rectR;

	int col_imageMatchDegree=M_rectG.rows;
	int row_imageMatchDegree=M_rectR.rows;
	double matchDegree;

	cv::Mat_<double> imageMatchDegree;
	//cv::Mat imageMatchDegree(row_imageMatchDegree,col_imageMatchDegree, CV_64FC1, cv::Scalar::all(0));
	//cout<<M_rectG<<endl;
	//cout<<M_rectR<<endl;

	for (int j=0;j<col_imageMatchDegree;j++)
	{
		rectG.clear();
		for(int k=0;k<M_rectG.cols;k++) rectG.push_back(M_rectG.row(j).at<double>(k));

		cv::Mat_<double> temp_imageMatchDegree;		

		for(int i=0;i<row_imageMatchDegree;i++)
		{
			rectR.clear();
			for(int k=0;k<M_rectR.cols;k++) rectR.push_back(M_rectR.row(i).at<double>(k));

			cout<<"Computing the match degree of rect_G [";printVector(rectG);cout<<"] and rect_R [";
			printVector(rectR);cout<<"]......\n";

			matchDegree=getMatchDegree(rectG,rectR);
			temp_imageMatchDegree.push_back(matchDegree);
			cout<<" "<<endl;
			//cout<<temp_imageMatchDegree.t()<<endl;
		}
		imageMatchDegree.push_back<double>(temp_imageMatchDegree.t());
		
	}
	imageMatchDegree=imageMatchDegree.t();
	imageMatchDegree=preprocess( imageMatchDegree);//retain the max value in each row of imageMatchDegree,other element are zeros.
	cout<<"The matrix of imageMatchDegree:\n(Note:imageMatchDegree(i,j) is the match degree of j-th M_rectG and i-th M_rectR):\n"<<imageMatchDegree<<endl;
	return imageMatchDegree;
}