#include<opencv2/opencv.hpp>//precompile
using namespace cv;
using namespace std;
//void colorReduce(Mat& inputImage,Mat& outputImage,int div);
void pixelUnification(Mat& inputImage,Mat& outputImage);

int main()
{
	Mat srcImage=imread("1.jpg");//create an original image and show it
	imshow("srcImage",srcImage);

	Mat dstImage;//create an image which is similar to zhe original one
	dstImage.create(srcImage.rows,srcImage.cols,srcImage.type());

//	colorReduce(srcImage,dstImage,32);//reduce colors
	
	pixelUnification(srcImage,dstImage);//make each pixel's value to (r+g+b)/3

	imshow("dstImage",dstImage);//show the dstImage

	waitKey(0);//quit if any key is pressed
}

/*void colorReduce(Mat& inputImage,Mat& outputImage,int div)
{
	outputImage=inputImage.clone();//copy the inputImage to the outputImage
	int row=outputImage.rows;//get the limiting condition which is used in the traversal
	int col=outputImage.cols*outputImage.channels();

	for(int i=0;i<row;i++)//use pointer to traverse the array to reduce colors
	{
		uchar* data=outputImage.ptr<uchar>(i);
		for(int j=0;j<col;j++)
		{
			data[j]=data[j]/div*div+div/2;
		}
	}
}*/

void pixelUnification(Mat& inputImage,Mat& outputImage)
{
	outputImage=inputImage.clone();
	int row=outputImage.rows;
	int col=outputImage.cols*outputImage.channels();

	for(int i=0;i<row;i++)//use pointer to traverse the array to make the r,g,b'value equal to the average of r,g,b
	{
		uchar* data=outputImage.ptr<uchar>(i);
		for(int j=0;j+3<col;j+=3)
		{
			int ave=(data[j]+data[j+1]+data[j+2])/3;
			data[j]=ave;
			data[j+1]=ave;
			data[j+2]=ave;
		}
	}
}
