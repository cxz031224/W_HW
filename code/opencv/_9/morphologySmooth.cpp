#include<iostream>//调用头文件；命名空间
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()//主函数
{
	Mat src=imread("9.png"),dst_1,dst_2,dst_3,dst_4;//创建多个Mat变量存储原图和经过腐蚀或膨胀后的图片
	
	dilate(src,dst_1,getStructuringElement(MORPH_RECT,Size(30,30)));//利用尺寸为（30，30）的矩形核进行膨胀操作

	erode(src,dst_2,getStructuringElement(MORPH_CROSS,Size(20,20)));//利用尺寸为（20，20）的交叉形核进行腐蚀操作

	dilate(dst_2,dst_3,getStructuringElement(MORPH_ELLIPSE,Size(25,25)));//对进行过腐蚀的图片再进行膨胀，即开运算，其中使用尺寸为（25，25）的椭圆核进行膨胀操作

	erode(dst_1,dst_4,getStructuringElement(MORPH_ELLIPSE,Size(35,35)));//对进行过膨胀的图片再进行腐蚀，即闭运算，其中使用尺寸为（35，35）的椭圆核进行腐蚀操作
	
	imshow("src",src);//显示各图片
	imshow("dilite",dst_1);
	imshow("erode",dst_2);
	imshow("open",dst_3);
	imshow("close",dst_4);
	waitKey(0);//按任意键退出
}

