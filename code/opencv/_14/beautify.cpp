#include<iostream>//调用头文件；命名空间；函数声明
#include<math.h>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
void gamma(Mat& inputImage,double x);

int main()
{
	Mat src_1=imread("14-1.jpg"),src_2=imread("14-2.jpg"),dst_1=src_1,dst_2=src_2;//定义Mat变量存储原图和预处理图


	//修改1
	imshow("src_1",src_1);//显示原图

	Mat dst_1_1,dst_1_2;//定义两个图层
	gamma(dst_1,2.5);//伽马变换提高亮度

//	GaussianBlur(dst_1,dst_1_2,Size(3,3),0,0);
	Sobel(dst_1,dst_1_2,CV_32F,1,0,3,1,1,BORDER_DEFAULT);//利用Sobel算子提取发丝图层
	convertScaleAbs(dst_1_2,dst_1_2);

	GaussianBlur(dst_1,dst_1_1,Size(17,17),0,0);//对原图进行高斯模糊祛痘
	gamma(dst_1_1,0.5);//降低亮度
	
//	imshow("dst_1_1",dst_1_1);
//	imshow("dst_1_2",dst_1_2);

	addWeighted(dst_1_1,0.95,dst_1_2,0.05,3,dst_1);//按19：1加权合并
	gamma(dst_1,0.8);//降低亮度
	imshow("dst_1",dst_1);//显示效果

	//修改图2，流程大致同图1
	dst_2=src_2;
	imshow("src_2",src_2);
	Mat dst_2_1=src_2,dst_2_2=src_2;

	gamma(dst_2_1,10);
	GaussianBlur(dst_2_1,dst_2_1,Size(23,23),0,0);
	gamma(dst_2_1,0.1);
//	imshow("test")

//	gamma(dst_2_2,5);

	Sobel(dst_2,dst_2_2,CV_32F,1,0,3,1,1,BORDER_DEFAULT);
	convertScaleAbs(dst_2_2,dst_2_2);
//	gamma(dst_2_2,1.05);
//	GaussianBlur(dst_2_2,dst_2_2,Size(5,5),0,0);

//	imshow("dst_2_1",dst_2_1);
//	imshow("dst_2_2",dst_2_2);
	addWeighted(dst_2_1,0.75,dst_2_2,0.25,3,dst_2);
	imshow("dst_2",dst_2);

	waitKey(0);
}

void gamma(Mat& inputImage,double x)//定义gamma变换函数
{
	int row=inputImage.rows;
	int col=inputImage.cols*inputImage.channels();

	for(int i=0;i<row;i++)
	{
		uchar* data=inputImage.ptr<uchar>(i);
		for(int j=0;j<col;j++)
			data[j]=pow((data[j]+0.5)/256,1/x)*256-0.5;
	}
}
	
