// Display the frames being captured by webcam. Store the current frame in output2 folder on left click 
// Name: Mohit Sharma
// Roll No. : 201505508

#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;

#define ESC_KEY			27
#define WAIT_BETWEEN_FRAMES	30
#define OUTPUT_FOLDER_NAME 	"output"

int fNo = 0;

void captureImage(int event, int x, int y, int flags, void* userdata) 	//Event handler for mouse to capture image		
{
	if(event == EVENT_LBUTTONDOWN)
	{
		char imgName[20] = {0};
		vector<int> compression_params; 			
		compression_params.push_back(CV_IMWRITE_JPEG_QUALITY); 	
		compression_params.push_back(100); 			
		sprintf(imgName, "%s/img%d.jpg", OUTPUT_FOLDER_NAME, fNo++);
		if(!imwrite(imgName, *(Mat*)userdata, compression_params))	//Write to image file
		{
			cout << "Failed to save the image\n";

		}
	}
}

void captureFramesFromCam()
{
	VideoCapture cap(0); 					// open the cam
	if(!cap.isOpened())
    	{
         	cout<<"Failed to open the file\n";
         	return;
    	}	
	Mat frame;
	namedWindow("Webcam",CV_WINDOW_AUTOSIZE);
	setMouseCallback("Webcam", captureImage, &frame);
	while(cap.read(frame))
    	{
    	       	imshow("Webcam", frame);
    	       	//cap.read(frame);
        	if(waitKey(WAIT_BETWEEN_FRAMES) == ESC_KEY)
       		{
                	cout<<"Exiting...\n"; 
                	break; 
       		}
    	}
	cap.release(); 
}

int main(int argc, char* argv[])
{
	captureFramesFromCam();
	return 0;
}
