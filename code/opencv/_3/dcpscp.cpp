#include<opencv2/opencv.hpp>//调用头文件；命名空间；函数声明
#include<iostream>
using namespace cv;
using namespace std;
void colorReduce(Mat& inputImage);

int main()//主函数
{
	Mat srcMat=imread("1.jpg"),deepMat,shallowMat;//定义三个Mat变量存储原图、深复制的图、浅复制的图

	shallowMat=srcMat.clone();//浅复制：调用方法clone()
	deepMat=srcMat;//深复制：直接赋值

	imshow("shallowMat",shallowMat);//显示修改srcMat前的两张图
	imshow("deepMat",deepMat);

	colorReduce(srcMat);//修改srcMat

	imshow("shallowMat2",shallowMat);//显示修改srcMat后的两张图
	imshow("deepMat2",deepMat);
	
	waitKey(0);//按任意键退出
}

void colorReduce(Mat& inputImage)//定义二值化函数
{
	int row=inputImage.rows;
	int col=inputImage.cols*inputImage.channels();
	uchar threshold=100;

	for(int i=0;i<row;i++)
	{
		uchar* data=inputImage.ptr<uchar>(i);
		for(int j=0;j+3<col;j+=3)
		{
			int ave=(data[j]+data[j+1]+data[j+2])/3;
			if(ave>threshold)
				ave=255;
			else ave=0;
			data[j]=data[j+1]=data[j+2]=ave;
		}
	}
}
