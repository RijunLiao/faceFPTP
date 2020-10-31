/* getFPTP function: Comput

*/


#include "cv.h"
#include "cxcore.h"
#include "highgui.h"

void getFPTP(int M_rectG[][4],int num_rectG,int M_rectR[][5],int num_rectR,int &FP,int &TP,int thresh)
{
	int rectG[4];
	int rectR[5];
	int flagFace;
	int flagFP;//The FP++ only if all M_rectR don't match the M_rectG[i][].


	for(int i=0;i<num_rectG;i++)
	{
		for(int i2=0;i2<4;i2++){rectG[i2]=M_rectG[i][i2];}// transform the i-th row of M_rectG into rectG
		flagFP=0;

		for(int j=0;j<num_rectR;j++)
		{
			for(int j2=0;j2<5;j2++){rectR[j2]=M_rectR[j][j2];}// transform the j-th row of M_rectR into rectR
			flagFace=isFace(rectG,rectR,thresh);

			flagFP=flagFP+flagFace;//The FP++ only if all M_rectR don't match the M_rectG[i][].
			if (flagFP==0) FP++;


			if (flagFace==1) 
			{
				TP++;
				M_rectR[j][4]=0;
			}



		}
	}

}