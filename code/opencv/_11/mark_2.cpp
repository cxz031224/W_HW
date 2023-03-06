#include<iostream>//调用头文件；命名空间；定义全局变量
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
Mat labels,stats,centroids;

int main()//主函数
{
	Mat img=imread("11.png"),src;//定义Mat存储原图和处理后的图
	imshow("img",img);//显示原图

	threshold(img,src,100,255,THRESH_BINARY_INV);//二值化：大于100设0，反之255
	erode(src,src,getStructuringElement(MORPH_RECT,Size(7,7)));//利用尺寸为（7，7）的矩形核进行腐蚀
	dilate(src,src,getStructuringElement(MORPH_ELLIPSE,Size(23,23)));//利用尺寸为（23，23）的椭圆核进行膨胀

	vector<Mat>channels;//分离通道并取蓝色通道
	split(src,channels);
	Mat dst=channels.at(0);
	int count=connectedComponentsWithStats(dst,labels,stats,centroids);//连通域计算并返回相关数据
//	imshow("src",src);//显示处理后的图片

	for(int i=1;i<count;i++)//绘制外接矩形框
	{
		Vec2d pt=centroids.at<Vec2d>(1,0);
		int x=stats.at<int>(i,CC_STAT_LEFT);
		int y=stats.at<int>(i,CC_STAT_TOP);
		int width=stats.at<int>(i,CC_STAT_WIDTH);
		int height=stats.at<int>(i,CC_STAT_HEIGHT);
		rectangle(img,Rect(x,y,width,height),Scalar(0,0,255),1,8,0);
	}
	imshow("ok",img);//显示标记后的图片
	cout<<count-1<<endl;//输出回形针数
	waitKey(0);//按任意键退出
}
