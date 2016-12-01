// Program to change persepective of images to a rectangle
// Name: Mohit Sharma
// Roll No. : 201505508

#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;

#define IMAGE2	"p3.jpg"

//double H1[] = {-3.87592060e-03,  -1.92119386e-04,  -9.65700909e-01};	//p1
//double H2[] = {-6.19051904e-04,  -3.60034531e-03,  -2.59532119e-01};
//double H3[] = {2.77954075e-06,  -7.07115167e-07,  -6.03563068e-03}; 

//double H1[] = {-3.91986198e-03,  -2.19890156e-03,  -3.16223569e-01};	//p2
//double H2[] = {1.74720015e-03,  -1.30122945e-03,  -9.48670706e-01};
//double H3[] = {-3.73612270e-06,  -1.75464010e-06,  -1.26489427e-03};

double H1[] = {8.95217273e-04,   1.46564478e-04,   4.97359733e-01};	//p3
double H2[] = {1.71737751e-04,   6.17119139e-04,   8.67540722e-01};
double H3[] = {-4.56606470e-07,   3.65698394e-07,   2.27104901e-03}; 


Mat A1 = Mat(3, 1, CV_32FC1, H1 );
Mat A2 = Mat(3, 1, CV_32FC1, H2 );
Mat A3 = Mat(3, 1, CV_32FC1, H3 );    
    
double multiply(double d[], double A[], int l)
{
	double sum = 0;
	for(int i = 0; i<l; i++ )
	{
		sum += d[i] * A[i];
	}
	return sum;
}
void perspectiveImage()							//change image persepective
{
	Mat image1(400, 600, CV_8UC3, Scalar(0));
 	Mat image2 = imread(IMAGE2, CV_LOAD_IMAGE_COLOR);
 	double pt[3] ={0};
 	pt[2] = 1;
 	if(!image1.data || !image2.data)
 	{
 		cout<<"Failed to read the images.\n";
 		return;
 	}
	vector<int> compression_params; 				
	compression_params.push_back(CV_IMWRITE_JPEG_QUALITY); 		
	compression_params.push_back(100); 
	for(int i = 0; i<image1.rows; i++)
	{
		for(int j = 0; j<image1.cols; j++)
		{
			pt[0] = j;
			pt[1] = i;
			Mat p = Mat( 3,1,  CV_32FC1, pt);
			double x = multiply(H1,pt,3);
			double y = multiply(H2,pt,3);
			double w = multiply(H3,pt,3);
			if( w == 0)
				w = 1;
			if(x/w>=0 && y/w>=0 && x/w<image2.cols && y/w< image2.rows)
				image1.at<Vec3b>(i,j) = image2.at<Vec3b>(abs(y/w), abs(x/w));
		}
	}
	if(!imwrite( "stiched.jpg", image1,  compression_params))
	{
		cout<<"Failed to write the image\n";
	}
	namedWindow( "Persepective Image", WINDOW_AUTOSIZE );
	imshow( "Persepective Image", image1 ); 
	waitKey(0);
}

int main(int argc, char* argv[])
{
	perspectiveImage();
	return 0;
}
