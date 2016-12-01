// Program to stich two images with overlapping regions (Use homography matrices from DLT, RANSAC, RANSAC using SIFT points) and display
// Name: Mohit Sharma
// Roll No. : 201505508

#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;

#define IMAGE1	"I1.jpg"
#define IMAGE2	"I2.jpg"

double H1[] = {-5.07645106e-04,   1.11822860e-03,  -9.94672411e-01};			//From DLT
double H2[] = {3.32904069e-04,  -1.66414422e-03,  -1.03023751e-01};
double H3[] = {2.45570295e-06,   2.27950479e-06,  -2.91764230e-03};

//double H1[] = {3.74593677e-03,   1.01456967e-03,   9.99167810e-01};			//From RANSAC
//double H2[] = {-4.89964652e-04,   4.82531104e-03,   4.00600116e-02};
//double H3[] = {-1.65324985e-06,   1.72202497e-06,  4.50535846e-03}; 

//double H1[] = {-0.0024,   -0.0001,   -0.9966};					//From SURF
//double H2[] = {0.0004,   -0.0033,   -0.0820};
//double H3[] = {0.0000,   -0.0000,   -0.0037}; 

//double H1[] = {-3.33563536e-03,  -3.30184892e-04,   9.56583196e-01};					//From SURF Planar
//double H2[] = {-2.60968909e-03,  9.43416437e-04,   2.91424172e-01};
//double H3[] = {-5.80231954e-06,  -4.02594341e-07,   1.26709868e-03};


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
void stichImages()							//Stich both images
{
	Mat image1 = imread(IMAGE1, CV_LOAD_IMAGE_COLOR);
	Mat image2 = imread(IMAGE2, CV_LOAD_IMAGE_COLOR);
	double pt[3] ={0};
	pt[2] = 1;
	if(!image1.data || !image2.data)
	{
		cout<<"Failed to read the images.\n";
		return;
	}
	Size sz1 = image1.size();
	Size sz2 = image2.size();
	Mat result(sz1.height + sz2.height, sz1.width+sz2.width, CV_8UC3);
	vector<int> compression_params; 				
	compression_params.push_back(CV_IMWRITE_JPEG_QUALITY); 		
	compression_params.push_back(100); 
	for(int i = 0; i<image1.rows; i++)
	{
		for(int j = 0; j<image1.cols; j++)
		{
			result.at<Vec3b>(i, j) = image1.at<Vec3b>(i, j);
		}
	}
	for(int i = 0; i<image2.rows; i++)
	{
		for(int j = 0; j<image2.cols; j++)
		{
			pt[0] = j;
			pt[1] = i;
			Mat p = Mat( 3,1,  CV_32FC1, pt);
			double x = multiply(H1,pt,3);
			double y = multiply(H2,pt,3);
			double w = multiply(H3,pt,3);
			if( w == 0)
				w = 1;
			if(x/w>=0 && y/w>=0 && x/w<result.cols && y/w< result.rows)
				result.at<Vec3b>(abs(y/w), abs(x/w)) = image2.at<Vec3b>(i, j);
      
		}
	}
	if(!imwrite( "stiched.jpg", result,  compression_params))	
	{
		cout<<"Failed to write the image\n";
	}
	namedWindow( "Stiched Image", WINDOW_AUTOSIZE );// Create a window for display.
	imshow( "Stiched Image", result ); 
	waitKey(0);
}

int main(int argc, char* argv[])
{
	stichImages();
	return 0;
}
