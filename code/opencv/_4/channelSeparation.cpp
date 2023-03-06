#include<opencv2/opencv.hpp>//调用头文件；命名空间；函数声明
#include<iostream>
using namespace cv;
using namespace std;
void channelSeparation(Mat& inputImage,Mat& outputImage_1,Mat& outputImage_2,Mat& outputImage_3);

int main()
{
	Mat srcImage=imread("1.jpg"),dstImage_1,dstImage_2,dstImage_3;//定义四个Mat变量存储原图和三个通道
	imshow("srcImage",srcImage);//显示原图

	channelSeparation(srcImage,dstImage_1,dstImage_2,dstImage_3);//调用通道分离函数

	imshow("dstImage_1",dstImage_1);//分别显示三个通道分离后的图片
	imshow("dstImage_2",dstImage_2);
	imshow("dstImage_3",dstImage_3);

	waitKey(0);	//按任意键退出
}

void channelSeparation(Mat& inputImage,Mat& outputImage_1,Mat& outputImage_2,Mat& outputImage_3)//函数定义
{
	vector<Mat> channels;//创建vector变量存储三个通道的值
	split(inputImage,channels);//通道分离
	outputImage_1=channels.at(0);//将三个通道的图片分别赋给输出图像1，2，3
	outputImage_2=channels.at(1);
	outputImage_3=channels.at(2);
}
