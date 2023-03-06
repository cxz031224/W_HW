#include<iostream>//调用头文件；命名空间
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()//主函数
{
	Mat img=imread("1.jpg");//读取图片存在Mat型变量img中
	imshow("img",img);//显示处理前的图片

	circle(img,Point(470,640),64,Scalar(0,0,255),-1,8);//在img中，以坐标为（470，640）的点为中心，64为半径，用红色作实心圆，8联通

	line(img,Point(360,520),Point(360,768),Scalar(255,0,0),2,8);//在img中，作从点（360，520）到点（360，768）线粗为2的蓝色的线，8联通
	line(img,Point(570,520),Point(570,768),Scalar(255,0,0),2,8);//从点（570，520）到点（570，768）

	ellipse(img,Point(360,520),Size(32,16),0,0,360,Scalar(0,0,255),2,8);//在img中，以点（360，520）为中心，在长为32，宽为16的矩形内，旋转角度为0，拓展弧度从0到360度，作线粗为2的红色的8联通的椭圆
	ellipse(img,Point(570,520),Size(32,16),0,0,360,Scalar(0,0,255),2,8);//以点（570，520）为中心

	/*Point point[1][4];
	point[0][0]=Point(150,400);
	point[0][1]=Point(600,400);
	point[0][2]=Point(150,100);
	point[0][3]=Point(600,100);
	
	const Point* ppt[1]={point[0]};
	int npt[]={4};
	fillPoly(img,ppt,npt,1,Scalar(0,255,0),8);*/
	rectangle(img,Rect(150,100,450,300),Scalar(0,255,0),1,8,0);//在img中，以点（150，100）为左上角，450为宽，300为高，作绿色的线粗为1的8联通的矩形，坐标中小数位数为0
	imshow("img1",img);//显示绘制后的图片
	waitKey(0);//按任意键退出
}
