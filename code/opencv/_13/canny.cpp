#include<iostream>//调用头文件；命名空间
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()//主函数
{
	Mat src=imread("1.jpg"),dst=src;//定义Mat变量存储原图与处理后的图片
	imshow("src",src);//显示原图
	//Canny(src,dst,30,20,3,false);
	
/*	dst=src.clone();
	int row=dst.rows,col=dst.cols*dst.channels();
	for(int i=0;i<row;i++)
	{
		uchar* data=dst.ptr<uchar>(i);
		for(int j=0;j+3<col;j+=3)
		{
			if((data[j]+data[j+1]+data[j+2])/3>125)
				data[j]=data[j+1]=data[j+2]=255;
			else
				data[j]=data[j+1]=data[j+2]=0;
		}
	}
	vector<Mat> channels;
	split(dst,channels);
	dst=channels.at(0);*/
	cvtColor(src,dst,COLOR_RGB2GRAY);//将图片从RGB模式转化为灰度图
	blur(dst,dst,Size(11,11));//对图片进行以核尺寸为（11，11）的均值滤波
//	erode(dst,dst,getStructuringElement(MORPH_ELLIPSE,Size(11,11)));
//	erode(dst,dst,getStructuringElement(MORPH_RECT,Size(11,11)));
//	imshow("erode",dst);
	Canny(dst,dst,15,14,3,false);//对原图使用第一滞后性阈值为15，第二滞后性阈值为14，sobel算子孔径大小为3的Canny算子

	imshow("canny",dst);//显示处理后的图片
	waitKey(0);//按任意键退出
}
