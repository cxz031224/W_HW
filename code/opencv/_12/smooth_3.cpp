#include<iostream>//调用头文件；命名空间
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()//主函数
{
	VideoCapture capture(0);//定义VideoCapture变量存储调用计算机摄像头的值
	Mat srcframe,dstframe_1,dstframe_2,dstframe_3;//定义Mat变量后续存储原画和滤波处理后的视频

	while(1)//死循环实时检测
	{
		if(!capture.isOpened())//摄像头没开
		{
			cout<<"你没开摄像头哦"<<endl;
			break;
		}
		else//开了摄像头
		{
			capture>>srcframe;//将原画传给srcframe
			imshow("srcframe",srcframe);//输出原画

			blur(srcframe,dstframe_1,Size(9,9),Point(-1,-1));//对原画进行尺寸为（9，9），锚点为核中心的均值滤波操作
			imshow("blur",dstframe_1);//输出经均值滤波处理后的原画
			
			GaussianBlur(srcframe,dstframe_2,Size(3,3),0,0);//对原画进行尺寸为（3，3），偏移差自动计算的高斯滤波操作
			imshow("GaussianBlur",dstframe_2);//输出经高斯滤波处理后的原画
			
			medianBlur(srcframe,dstframe_3,55);//对原画进行线性尺寸为55的孔径的中值滤波操作
			imshow("medianBlur",dstframe_3);//输出经中值滤波处理后的原画

			char c=waitKey(30);//按下esc后退出
			if(c==27)break;
		}
	}
}


