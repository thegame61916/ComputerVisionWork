// Chroma Keying: Merge two videos (one with green backgournd) in one
// Name: Mohit Sharma
// Roll No. : 201505508

#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;

#define MAX_FRAMES		30
#define FRAME_RATE		30
#define VIDEO_GREEN_NAME	"input/green.mp4"		//Video with green bg
#define VIDEO_NORMAL_NAME	"input/normal.mp4"		//Normal video
#define VIDEO_MERGED_NAME	"output/merged.avi"		//merged video name
#define ESC_KEY			27
#define WAIT_BETWEEN_FRAMES	30

void displayMergedVideo()				//Display the merged video
{
	Mat frame;
	VideoCapture cap(VIDEO_MERGED_NAME);
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
    	cap.release();
}

void mergeVideos()							//Merge both the videos
{
	VideoCapture capG(VIDEO_GREEN_NAME); 				// open the video with green BG
	VideoCapture capN(VIDEO_NORMAL_NAME); 				// open the normal video
	if(!capG.isOpened() || !capN.isOpened())
	{
		cout<<"Failed to open the file\n";
		return;
	}
	int fNo = 0;
	Mat frameG;							//Frame of video with green bg
	Mat frameN;							//Frame of normal video
	double dWidth = capG.get(CV_CAP_PROP_FRAME_WIDTH);		//get the width of video
   	double dHeight = capG.get(CV_CAP_PROP_FRAME_HEIGHT);		//get the height of video
   	Size frameSize(static_cast<int>(dWidth), static_cast<int>(dHeight));
	VideoWriter VW(VIDEO_MERGED_NAME, CV_FOURCC('M', 'P', '4', '2'), FRAME_RATE, frameSize, true); 
	
	if(!VW.isOpened())
   	{
        	cout<<"Failed to create video writer\n";
        	return;
   	}
	while(fNo<MAX_FRAMES)						//Extract MAX_FRAMES from both the videos and merge
	{
		if(!capG.read(frameG) || !capN.read(frameN))
		{
			cout<<"Failed to read a frame from video\n";
			capG.release();
			capN.release(); 
			break;
		}
		for(int i = 0; i<frameG.rows; i++)
		{
			for(int j = 0; j<frameG.cols; j++)
			{
				if(i>= frameN.rows || j>=frameN.cols)	//If normal video has higher resolution than green one
					continue;
				Vec3b intensity = frameG.at<Vec3b>(i, j);
				if((int)intensity[0] >= 0 && (int)intensity[0] <= 20 && 
					(int)intensity[1] >= 230 && (int)intensity[1] <= 250 && 
					(int)intensity[2] >= 65 && (int)intensity[2] <= 85)
				{
					frameG.at<Vec3b>(i, j) = frameN.at<Vec3b>(i, j);	//replace green coloured pixel
				}
			}
		}
		VW.write(frameG);					//Write the merged frame
		fNo++;
	}
	capG.release();
	capN.release(); 
	displayMergedVideo();
}

int main(int argc, char* argv[])
{
	mergeVideos();
	return 0;
}
