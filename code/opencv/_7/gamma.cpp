#include<iostream>//调用头文件；命名空间；函数声明
#include<math.h>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
void gamma(Mat& inputImage);

int main()//主函数
{
	Mat img_1=imread("7-1.png"),img_2=imread("7-2.jpg");//读取两张图片
	imshow("img_1_1",img_1);//显示两张图片
	imshow("img_2_1",img_2);

	gamma(img_1);//伽马矫正两张图片
	gamma(img_2);

	imshow("img_1_2",img_1);//显示矫正后的图片
	imshow("img_2_2",img_2);

	waitKey(0);//按任意键退出
}

void gamma(Mat& inputImage)//定义伽马矫正（幂律变换）函数，用于图像增强，提升或减小暗部细节，通过非线性变换让图像从曝光强度的线性响应变得更接近人眼感受的响应，即对曝光过多或不足的图片进行矫正
{
	int row=inputImage.rows;//取输入图片的行数
	int col=inputImage.cols*inputImage.channels();//取输入图片的列数*通道数

	for(int i=0;i<row;i++)//用for循环遍历像素
	{
		uchar* data=inputImage.ptr<uchar>(i);//取行地址？
		for(int j=0;j<col;j++)
			data[j]=pow((data[j]+0.5)/256,1/2.2)*256-0.5;//伽马变换：先归一化，然后通过乘方预补偿，最后反归一化
	}
}
