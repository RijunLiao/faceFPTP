/* getMatchDegree function: compute the Match Degree of two rectangle

vector<double> rectG: input one rectangle [x,y,w,h] that from Grounf Truth.txt
vector<double> rectR: input one rectangle [x,y,w,h] that from result.txt
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

double getMatchDegree(vector<double> rectG,vector<double> rectR)
{

	int areaInter;//The area of intersection of two rectangle 
	int areaUnion;//The area of union of two rectangle
	double MatchDegree;

	cv::Rect R1(rectG.at(0),rectG.at(1),rectG.at(2),rectG.at(3));
	cv::Rect R2(rectR.at(0),rectR.at(1),rectR.at(2),rectR.at(3));
	cv::Rect R3=R1&R2;

	areaInter=R3.width*R3.height;
	areaUnion=R1.width*R1.height+R2.width*R2.height-areaInter;
	MatchDegree=areaInter*1.0/areaUnion;


	printf("areaInter:%6d\t",areaInter);
	printf("areaUnion:%6d\t",areaUnion);
	printf("MatchDegree:%6f\n",MatchDegree);

	return MatchDegree;
}