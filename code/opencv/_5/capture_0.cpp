#include<opencv2/opencv.hpp>//调用头文件；命名空间
#include<string>
#include<iostream>
#include<stdlib.h>
#include<stdio.h>
using namespace std;
using namespace cv;

int main()//主函数
{
	VideoCapture capture(0);//定义VideoCapture存储调用计算机摄像头得到的值
	double fps=0;//定义并初始化fps
	double t=0;//定义并初始化时间
	char str[10];//定义一个字符串存储fps的值
	Mat frame;//定义Mat变量接收capture的值

	while(1)//用死循环检测摄像头
	{
		t=(double)getTickCount();//计时开始
		if(!capture.isOpened())//没开摄像头
		{
			cout<<"你tm没开摄像头"<<endl;
			break;
		}
		else//开了摄像头
		{
			capture>>frame;//将capture的值传给frame
			t=((double)getTickCount()-t)/getTickFrequency();//计算结束时间（getTickCount()返回从操作系统到当前所经过的毫秒数；getTickFrequency()返回每秒的计时周期数）
			fps=1.0/t;//计算fps
			sprintf(str,"%.2f",fps);//把fps转化为字符串
			string FPS="fps:";//连接各字符串
			FPS+=str;
			//printf("fps:%.2f width:%d height:%d fps:%.2f",fps,frame.cols,frame.rows,capture.get(CAP_PROP_FPS));
			putText(frame,FPS,Point(450,460),FONT_HERSHEY_SIMPLEX,1,Scalar(0,255,0));//在画面上输出字符串（左下角坐标（450，460），字体为FONT_HERSHEY_SIMPLEX，线粗1，蓝色）
			imshow("camera",frame);//实时显示摄像头输入的画面及帧数
			char c=waitKey(50);//按下esc时退出
			if(c==27)break;
		}
	}
}

