// Chroma Keying: Merge two videos (one with green backgournd) in one
// Name: Mohit Sharma
// Roll No. : 201505508

#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;

#define IMAGE1	"I1.jpg"
#define IMAGE2	"I2.jpg"

double H1[] = {3.74593677e-03,   1.01456967e-03,   9.99167810e-01};
double H2[] = {-4.89964652e-04,   4.82531104e-03,   4.00600116e-02};
double H3[] = {-1.65324985e-06,   1.72202497e-06,  4.50535846e-03}; 

Mat A1 = Mat(3, 1, CV_32FC1, H1 );
    Mat A2 = Mat(3, 1, CV_32FC1, H2 );
    Mat A3 = Mat(3, 1, CV_32FC1, H3 );    
    
double multiply(double d[], double A[], int l){
	double sum = 0;
	for(int i = 0; i<l; i++ ){
		sum += d[i] * A[i];
	}
	return sum;
}
void stichImages()							//Merge both the videos
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
	//Mat result(image1);
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
			//cout<<p;
			double x = multiply(H1,pt,3);
			double y = multiply(H2,pt,3);
			double w = multiply(H3,pt,3);
			//cout << x <<"  "<<y<<"  "<<w <<"\n";
			if( w == 0)
				w = 1;
			if(x/w>=0 && y/w>=0 && x/w<result.cols && y/w< result.rows)
//cout<<(abs(x/w))<<"\n";
			result.at<Vec3b>(abs(y/w), abs(x/w)) = image2.at<Vec3b>(i, j);	//replace green coloured pixel
			//else{
			//double t = x/w;
			//cout<<t<<w<<"no\n";
			//}
		}
	}
	if(!imwrite( "stiched.jpg", result,  compression_params))
	{
		cout<<"Failed to write the image\n";
	}
}

int main(int argc, char* argv[])
{
	stichImages();
	return 0;
}
