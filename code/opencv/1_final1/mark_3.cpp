#include<iostream>//调用头文件；命名空间
#include<opencv2/opencv.hpp>
#include<vector>
using namespace std;
using namespace cv;

int main()//主函数
{
	Mat src=imread("1.jpg");//读取图片
	imshow("src",src);//显示原图


	Mat dst=src.clone();//复制原图

	//闭运算
	dilate(dst,dst,getStructuringElement(MORPH_ELLIPSE,Size(15,15)));//使用尺寸为（15，15）的椭圆核进行膨胀
	erode(dst,dst,getStructuringElement(MORPH_ELLIPSE,Size(9,9)));//使用尺寸为（9，9）的椭圆核进行腐蚀

	threshold(dst,dst,99.5,255,THRESH_BINARY_INV);//二值化：大于97设0，反之255

//	imshow("ssrc",src);
	//开运算
	erode(dst,dst,getStructuringElement(MORPH_ELLIPSE,Size(17,17)));//使用尺寸为（17，17）的椭圆核进行腐蚀
	dilate(dst,dst,getStructuringElement(MORPH_ELLIPSE,Size(21,21)));//使用尺寸为（21，21）的椭圆核进行膨胀

	vector<Mat> channels;//创建一个vector变量存储各通道值
	split(dst,channels);//分离通道
	dst=channels.at(0);//取一个通道
	Mat labels,stats,centroids;
	int count=connectedComponentsWithStats(dst,labels,stats,centroids);//进行连通域计算

//	imshow("sssrc",src);
	//去除过小区域，初始化颜色表
	Mat img_color;	
	vector<Vec3b> colors(count);
	colors[0]=Vec3b(0,0,0);
	for(int i=1;i<count;i++)
	{
		colors[i]=Vec3b(255,255,255);
		//面积阈值筛选
		if((stats.at<int>(i,CC_STAT_AREA))>80*80)
			colors[i]=Vec3b(0,0,0);
	}
	//按照label值，对不同连通域进行着色
	img_color=Mat::zeros(dst.size(),CV_8UC3);
	for(int y=0;y<img_color.rows;y++)
		for(int x=0;x<img_color.cols;x++)
		{
			int label=labels.at<int>(y,x);
			CV_Assert(0<=label&&label<=count);
			img_color.at<Vec3b>(y,x)=colors[label];
		}
	//统计降噪后的连通区域
	cvtColor(img_color,dst,COLOR_BGR2GRAY);
	vector<vector<Point>> contours;//创建vector变量存储连通域
	findContours(dst,contours,RETR_LIST,CHAIN_APPROX_SIMPLE);//找到各连通域并存入vector变量contours中
	drawContours(src,contours,-1,Scalar(0,255,255),-1,8);//作出连通域
		

	imshow("dst",src);//显示效果图
	waitKey(0);//按任意键退出
}
