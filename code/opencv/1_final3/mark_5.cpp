#include<iostream>//调用头文件；命名空间
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()//主函数
{
	Mat img=imread("1.jpg"),IMG=img.clone();//读取图片
	imshow("img1",img);//显示原图
	
	cvtColor(IMG,IMG,COLOR_RGB2HSV);//将RGB模式转化为HSV模式存在IMG中

	Mat IMG2=IMG;//定义一个新Mat存储修改后的IMG
	inRange(IMG,Scalar(100,50,50),Scalar(150,255,255),IMG2);//通过inRange函数实现瓶盖的提取
	erode(IMG2,IMG2,getStructuringElement(MORPH_ELLIPSE,Size(25,25)));//腐蚀去噪

	dilate(IMG2,IMG2,getStructuringElement(MORPH_ELLIPSE,Size(25,25)));//膨胀还原
	vector<Mat>channels;//拆出一个通道
	split(IMG2,channels);
	IMG2=channels.at(0);
	Mat labels,stats,centroids;
	int count=connectedComponentsWithStats(IMG2,labels,stats,centroids);//计算连通域

	for(int i=1;i<count;i++)//绘制识别框
	{
		Vec2d pt=centroids.at<Vec2d>(1,0);
		int x=stats.at<int>(i,CC_STAT_LEFT);
		int y=stats.at<int>(i,CC_STAT_TOP);
		int width=stats.at<int>(i,CC_STAT_WIDTH);
		int height=stats.at<int>(i,CC_STAT_HEIGHT);
		rectangle(img,Rect(x,y,width,height),Scalar(255,0,0),5,8,0);
	}
	imshow("img2",img);//显示修改后的图片

	waitKey(0);//按任意键退出
}
