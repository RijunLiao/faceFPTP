/* isFace function: determine whether the two faces match

int rectG[4]: input one rectangle [x,y,w,h] that from Grounf Truth.txt
int rectR[4]: input one rectangle [x,y,w,h,p] that from result.txt

flagFace: (output), two faces match if flagFace=1
					two faces don't match if flagFace=0

*/



#include "cv.h"
#include "cxcore.h"
#include "highgui.h"

int isMatch(int rectG[4],int rectR[4])
{
	int flagMatch;
	int areaInter;//The area of intersection of two rectangle 
	int areaUnion;//The area of union of two rectangle

		cv::Rect R1(rectG[0],rectG[1],rectG[2],rectG[3]);
		cv::Rect R2(rectR[0],rectR[1],rectR[2],rectR[3]);
		cv::Rect R3=R1&R2;

		areaInter=R3.width*R3.height;
		areaUnion=R1.width*R1.height+R2.width*R2.height-areaInter;
		printf("areaInter:%6d\t",areaInter);
		printf("areaUnion:%6d\t",areaUnion);
		printf("areaInter*1.0/areaUnion:%6f\t",areaInter*1.0/areaUnion);
		//printf("areaUnion:%6f\n",areaInter*1.0/areaUnion);
		//Note: areaUnion maybe equal to zero. 
		if (areaInter*1.0/areaUnion<0.5)
		{
			flagMatch=0;
		}
		else
		{
			flagMatch=1;
		}


	printf("flagMatch:%6d\n",flagMatch);

	return flagMatch;
}