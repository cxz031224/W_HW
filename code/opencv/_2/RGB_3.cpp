#include<opencv2/opencv.hpp>//调用头文件
#include<iostream>
using namespace cv;//使用命名空间
using namespace std;
void colorReduce(Mat& inputImage,Mat& outputImage);//函数声明

int main()//主函数
{
	Mat srcImage=imread("1.jpg");//创建Mat变量，读取图片，命名为srcImage
	imshow("srcImage",srcImage);//展示刚读取的文件

	Mat dstImage;//定义dstImage
	dstImage.create(srcImage.rows,srcImage.cols,srcImage.type());//复制srcImage的行列类型

	colorReduce(srcImage,dstImage);//调用函数colorReduce将每个像素的值二值化

	imshow("dstImage",dstImage);//展示修改后的图片
	waitKey(0);//按任意键结束程序
}

void colorReduce(Mat& inputImage,Mat& outputImage)//定义colorReduce函数
{
	outputImage=inputImage.clone();//深复制
	int row=outputImage.rows;//取行数
	int col=outputImage.cols*outputImage.channels();//取列数
	uchar threshold=100;//定义阈值

	for(int i=0;i<row;i++)//for循环遍历像素
	{
		uchar* data=outputImage.ptr<uchar>(i);//取每行首地址？
		for(int j=0;j+3<col;j+=3)
		{
			int ave=(data[j]+data[j+1]+data[j+2])/3;//取每个像素三通道的平均值
			if(ave>threshold)//得到要赋的值
				ave=255;
			else ave=0;
			data[j]=data[j+1]=data[j+2]=ave;//赋值
		}
	}
}

