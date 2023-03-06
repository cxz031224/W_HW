#include<iostream>//调用头文件；命名空间
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()//主函数
{
	Mat img=imread("8.png"),IMG=img;//读取图片
	imshow("img1",img);//显示原图
	
	cvtColor(img,IMG,COLOR_RGB2HSV);//将RGB模式转化为HSV模式存在IMG中

	Mat IMG2=IMG;//定义一个新Mat存储修改后的IMG
	inRange(IMG,Scalar(120,255,255),Scalar(120,255,255),IMG2);//通过inRange函数实现红色像素（H=120）的提取
	imshow("img2",IMG2);//显示修改后的图片

	waitKey(0);//按任意键退出
}
