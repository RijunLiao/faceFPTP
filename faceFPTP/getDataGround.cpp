//getDataGround : get data from the "Ground Truth.txt"
//
//Mat_<double> dataGroundTruth:(output) a matrix of [x y w h] of all the image
//vector<int> &indexGroundTruth :(output) a vector of number of [x y w h] in one image

#include "cv.h"
#include "cxcore.h"
#include "highgui.h"

#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <cstdlib>
using namespace std;
using namespace cv;  

void split(string& str, const char* c,vector<double> &res);// split the a line string into digital


Mat_<double> getDataGround(vector<int> &indexGroundTruth)
{

	//vector<double>  dataGroundTruth;
	Mat_<double> dataGroundTruth;
	Mat_<double> dataGroundTruth_temp;
		//vector<double>  indexGroundTruth;
	ifstream infile("Ground Truth.txt");
	string line;
	const char* space = " ";

	//返回的数据
	string filename;	//文件名
	int line_num;		//数据的行数
	vector<double> data;	//数据

	if (infile) // 有该文件
	{
		ifstream in("Ground Truth.txt");	//重新打开
		while (getline(in, line)) // line中不包括每行的换行符
		{
			data.clear();
			//int order = 0;
			if (line.find(".jpg", 0) != string::npos) {
				filename.assign(line);
				getline(in, line);
				line_num = atoi(line.c_str());
				indexGroundTruth.push_back(line_num);

				if (line_num!=0)
				{
					int num = line_num;
					while (num > 0) {
						num--;
						getline(in, line);
						split(line, space, data);
					}
					//order++;

					int data_num = data.size();
					int line_len = data.size() / line_num;

					for (int i = 0; i < data_num; ) {

						dataGroundTruth_temp.push_back(data.at(i));
						//cout << data[i] << " ";
						i++;
						if (i % line_len == 0)
						{
							//cout<<dataGroundTruth_temp<<endl;
							dataGroundTruth.push_back<double>(dataGroundTruth_temp.t());
							dataGroundTruth_temp.pop_back(dataGroundTruth_temp.rows);

						}
					}
				}
			}


		}
	}
	else // 没有该文件
	{
		cout << "no such file" << endl;
	}

	return dataGroundTruth;
}