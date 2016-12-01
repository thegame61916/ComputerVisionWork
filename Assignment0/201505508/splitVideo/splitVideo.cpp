// Split a video in images, merge the images back to video and store everything in output1 folder
// Name: Mohit Sharma
// Roll No. : 201505508
#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;


#define MAX_FRAMES		100				//Max frames to be splitted
#define FRAME_RATE		20
#define VIDEO_NAME		"jl.mp4"
#define ESC_KEY			27
#define WAIT_BETWEEN_FRAMES	30
#define OUTPUT_FOLDER_NAME 	"output"			//Output folder

void splitVideoInimages()
{
	VideoCapture cap(VIDEO_NAME);
	if(!cap.isOpened())
    	{
         	cout<<"Failed to open the file\n";
         	return;
    	}
	vector<int> compression_params; 				
	compression_params.push_back(CV_IMWRITE_JPEG_QUALITY); 		
	compression_params.push_back(100); 				
	int fNo = 0;
	char imgName[20] = {0};
	Mat frame;
	
	while(fNo<MAX_FRAMES && cap.read(frame))
	{
		sprintf(imgName, "%s/img%d.jpg", OUTPUT_FOLDER_NAME, fNo++);
		if(!imwrite(imgName, frame, compression_params))	//Write to image file
		{
			cout<<"Failed to save the image\n";

		}
	}
	cap.release(); 
}

void combineImagesInVideoAndDisplay()
{
	Mat frame;
	char imgName[20] = {0};
	char vdoName[20] = {0};
	sprintf(vdoName, "%s/MyVideo.avi", OUTPUT_FOLDER_NAME);
	sprintf(imgName, "%s/img%d.jpg", OUTPUT_FOLDER_NAME, 0);
	frame = imread(imgName, CV_LOAD_IMAGE_UNCHANGED); 		//To get image width and height 
	double dWidth = frame.cols; 					//get the width of frames of the video
   	double dHeight = frame.rows; 					//get the height of frames of the video
	Size frameSize(static_cast<int>(dWidth), static_cast<int>(dHeight));
	VideoWriter VW(vdoName, CV_FOURCC('M', 'P', '4', '2'), FRAME_RATE, frameSize, true); 
	
	if(!VW.isOpened())
   	{
        	cout<<"Failed to write the video\n";
        	return;
   	}
	for(int i = 0; i<MAX_FRAMES; i++)
	{
		sprintf(imgName, "%s/img%d.jpg", OUTPUT_FOLDER_NAME, i);
		frame = imread(imgName, CV_LOAD_IMAGE_UNCHANGED);
     		if(frame.empty())
     		{
			cout << "Failed to read the image\n";
			return;
	     	}
	     	VW.write(frame);
	}
	VideoCapture cap(vdoName);
	if(!cap.isOpened())
    	{
         	cout<<"Failed to open the file\n";
         	return;
    	}
    	
    	while(cap.read(frame))
    	{
    	       	imshow("Created Video", frame);
        	if(waitKey(WAIT_BETWEEN_FRAMES) == ESC_KEY)
       		{
                	cout<<"Exiting...\n"; 
                	break; 
       		}
    	}
}

int main(int argc, char* argv[])
{
	splitVideoInimages();
	combineImagesInVideoAndDisplay();
	return 0;
}
