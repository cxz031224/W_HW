#include<iostream>//调用头文件；命名空间；函数声明
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
void gamma(Mat& inputImage,double x);

int main()//主函数
{
	Mat src=imread("1.jpg");//存储原图
	imshow("src",src);//显示原图

	Mat dst=src.clone();//浅复制

	gamma(dst,0.3);	//利用gamma变换降低亮度
//	dilate(dst,dst,getStructuringElement(MORPH_ELLIPSE,Size(15,15)));
	erode(dst,dst,getStructuringElement(MORPH_ELLIPSE,Size(13,13)));//利用尺寸为（13，13）椭圆核对图片进行腐蚀操作
	
//	gamma(dst,3.3);
	threshold(dst,dst,25,255,THRESH_BINARY);//二值化

	erode(dst,dst,getStructuringElement(MORPH_ELLIPSE,Size(5,5)));//利用尺寸为（5，5）的椭圆核对图片进行腐蚀去噪
	dilate(dst,dst,getStructuringElement(MORPH_ELLIPSE,Size(23,23)));//利用尺寸为（23，23）的椭圆核对图片进行膨胀合并各连通域
	
//	imshow("ssrc",dst);
	vector<Mat> channels;//通道分离
	split(dst,channels);
	dst=channels.at(0);//
	Mat labels,stats,centroids;
	int count=connectedComponentsWithStats(dst,labels,stats,centroids);//计算连通域

//	imshow("sssrc",dst);

	for(int i=1;i<count;i++)//绘制连通域
	{
		Vec2d pt=centroids.at<Vec2d>(1,0);
		int x=stats.at<int>(i,CC_STAT_LEFT);
		int y=stats.at<int>(i,CC_STAT_TOP);
		int width=stats.at<int>(i,CC_STAT_WIDTH);
		int height=stats.at<int>(i,CC_STAT_HEIGHT);
		rectangle(src,Rect(x,y,width,height),Scalar(0,255,0),7,8,0);
	}
	imshow("dst",src);
	waitKey(0);//按任意键退出
}

void gamma(Mat& inputImage,double x)//定义gamma变换函数
{
	int row=inputImage.rows;
	int col=inputImage.cols*inputImage.channels();
	for(int i=0;i<row;i++)
	{
		uchar* data=inputImage.ptr<uchar>(i);
		for(int j=0;j<col;j++)
			data[j]=pow((data[j]+0.5)/256,1/x)*256-0.5;
	}
}
