#include<iostream>//调用头文件；命名空间；定义全局变量
#include<algorithm>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
Mat labels,stats,centroids;

int main()//主函数
{
	Mat img=imread("10.png"),src;//创建Mat变量存储原图和处理后的图
	imshow("img",img);//显示原图

	threshold(img,src,85,255,THRESH_BINARY);//二值化，大于85取255，反之取0（THRESH_BINARY模式）
	dilate(src,src,getStructuringElement(MORPH_ELLIPSE,Size(5,5)));//利用尺寸为（5，5）的椭圆形核进行膨胀，过滤部分黑色杂质

	vector<Mat> channels;//创建vector变量储存分离通道后的三个通道的值
	split(src,channels);//分离通道
	Mat dst=channels.at(0);//取蓝色通道的值
	int count=connectedComponentsWithStats(dst,labels,stats,centroids);//计算连通域并返回连通域数，标签，统计信息（左上角点坐标，高，宽），重心
//	imshow("src",src);

	for(int i=1;i<count;i++)//绘制连通域的外接四边形
	{
		Vec2d pt=centroids.at<Vec2d>(1,0);//定义Vec2d变量存储连通域重心
		int x=stats.at<int>(i,CC_STAT_LEFT);//取出统计信息
		int y=stats.at<int>(i,CC_STAT_TOP);
		int width=stats.at<int>(i,CC_STAT_WIDTH);
		int height=stats.at<int>(i,CC_STAT_HEIGHT);
		rectangle(img,Rect(x,y,width,height),Scalar(255,255,0),1,8,0);//绘制矩形
	}
	imshow("ok",img);//显示处理后的图片
	cout<<count-1<<endl;//输出硬币数（要把整个图片的连通域1减掉）
	waitKey(0);//按任意键退出
}

