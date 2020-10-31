/* getTP function: Compute the True Positive of two images.

int M_rectG[][4]: the data of one image that from Grounf Truth.txt
int num_rectG:	  the number of rectangle in one image which from Grounf Truth.txt
int M_rectR[][5]: the data of one image that from result.txt
int num_rectR:    the number of rectangle in one image which from result.txt

isFace function: determine whether the two faces match

*/


#include "cv.h"
#include "cxcore.h"
#include "highgui.h"

int isMatch(int rectG[4],int rectR[4]);

int getTP(int M_rectG[][4],int num_rectG,int M_rectR[][5],int num_rectR)
{
	int rectG[4];
	int rectR[4];
	int flagMatch;
	int TP=0;


	for(int j=0;j<num_rectR;j++) M_rectR[j][4]=0;//Make the 'threshold' transform the 'state',if 'state==0': the j-th row of M_rectR don't match the face
												//if 'state==1': the j-th row of M_rectR already match the face

	for(int i=0;i<num_rectG;i++)
	{
		printf("The %4i-th row of M_rectG is going to match the rows of M_rectR...................\n",i);
		flagMatch=0;
		for(int i2=0;i2<4;i2++){rectG[i2]=M_rectG[i][i2];}// transform the  row of M_rectG into rectG

		for(int j=0;j<num_rectR;j++)
		{
			for(int j2=0;j2<4;j2++){rectR[j2]=M_rectR[j][j2];}// transform the j-th row of M_rectR into rectR


			if (M_rectR[j][4]==0) //if 'state==0': the j-th row of M_rectR havn't match the face
			{
				flagMatch=isMatch(rectG,rectR);

				if (flagMatch==1) 
				{
					TP++;
					M_rectR[j][4]=1;//
					printf("The %4d-th row of M_rectG is match the %4d-th row of M_rectR\n\n",i,j);
					break;// Break the inner for-loop when found the match two faces.
				}

			}
		}

		if (flagMatch==0) printf("The %4i-th row of M_rectG have not found the match rows in the M_rectR\n\n",i);

	}

	return TP;

}