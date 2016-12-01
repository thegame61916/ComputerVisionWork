// Chroma Keying: Merge two videos (one with green backgournd) in one
// Name: Mohit Sharma
// Roll No. : 201505508

#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;

#define IMAGE1	"b3.jpg"
#define IMAGE2	"t3.jpg"


 
//double H1[] = {2.79277865e-03,   3.66389838e-03,   6.10082058e-01};		//green field
//double H2[] = { -1.51401163e-04,   9.46477090e-04,   7.92314361e-01 };
//double H3[] = { 1.78322017e-07,  -1.83507158e-06,   3.96157180e-03}; 

//double H1[] = { 6.43662982e-04,   5.95565215e-18,   0.00000000e+00};		//pool
//double H2[] = { -5.84299389e-04,   5.91195960e-04,   9.99984995e-01};
//double H3[] = {-3.96774510e-06,   6.56501131e-07,   5.37626341e-03}; 

double H1[] = {9.93976017e-04,   2.24413193e-03,   7.20625502e-01};		//pool table
double H2[] = {-1.98992283e-04,   4.69429308e-04,   6.93259976e-01};
double H3[] = {8.38027667e-07,  -2.00182384e-06,   9.12184179e-03}; 

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
	Mat image1 = imread(IMAGE1, CV_LOAD_IMAGE_COLOR);
 	Mat image2 = imread(IMAGE2, CV_LOAD_IMAGE_COLOR);
 	double pt[3] ={0};
 	pt[2] = 1;
 	if(!image1.data || !image2.data)
 	{
 		cout<<"Failed to read the images.\n";
 		return;
 	}
	Mat result(image1);
	vector<int> compression_params; 				
	compression_params.push_back(CV_IMWRITE_JPEG_QUALITY); 		
	compression_params.push_back(100); 
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
	namedWindow( "Persepective Image", WINDOW_AUTOSIZE );
	imshow( "Persepective Image", result ); 
	waitKey(0);
}

int main(int argc, char* argv[])
{
	perspectiveImage();
	return 0;
}
