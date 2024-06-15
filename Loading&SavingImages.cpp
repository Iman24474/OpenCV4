#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

void onMouse(int event, int x, int y, int flags, void* param);

int main()
{
	// #1 Create an empty image object
	Mat image;
	// #2 Read an image from the file
	//image = imread("images/puppy.bmp");
	// #2.1 Read the input image as a gray-scale image
	image = imread("images/puppy.bmp", IMREAD_GRAYSCALE);
	// #2.2 Read the input image as a 3-channel color image
	//image = imread("images/puppy.bmp", IMREAD_COLOR);

	// #3 Error handling 
	if (image.empty())
	{
		cout << "No image is found!" << endl;
	}

	// #4 Drawing on images (the modifications to the image should be done before the 'imshow' call )

	// The examples of basics shape-drawing functions are 'circle', 'ellipse', 'line', and 'rectangle'
	circle(image, // destination image
		Point(155, 110), // center coordinate
		65, // radius
		0, // color (here black)
		3); // thickness

	// Writing text on the image
	putText(image, // destination image
		"This is a dog.", // text
		Point(40, 200), // text position
		FONT_HERSHEY_PLAIN, // font type
		2.0, // font scale
		255, // text color (here white)
		2); // text thickness

	// #5 Show the image
	imshow("Original Image", image);

	// #6 Apply some processing to the image
	Mat result; // Create another empty image
	flip(image, result, 1); // Positive for horizontal
							// 0 for vertical
							// Negative for both

	// Displaying the result in a new window
	imshow("Output Image", result);


	// #7 Save the processed image on the disk
	imwrite("output.bmp", result); // save result
								  // The file extension determines which codec will be used to save the image.

	// #8 Clicking on images using mouse
	setMouseCallback("Original Image", onMouse, reinterpret_cast<void*>(&image));


	// #9 Add a function to wait for a user keypress before ending the program (Always should be the last)
	waitKey(0); // 0 to indefinitely wait for a key pressed
				// Specifying a positive value will wait for the given amount of msec

	return 0;
}

// Callback function
//		The first parameter is an integer used to specify which type of mouse event has triggered
//			ex: EVENT_MOUSE_MOVE; EVENT_LBUTTONUP; EVENT_RBUTTONDOWN; EVENT_RBUTTONUP
//		The other two parameters are the pixel coordinates of the mouse location
//		The flags are used to determine which button was pressed when the mouse event was triggered
//		The last parameter is used to send an extra parameter to the function
void onMouse(int event, int x, int y, int flags, void* param)
{
	Mat* im = reinterpret_cast<Mat*>(param);
	switch (event) // dispatch the event
	{
	case EVENT_LBUTTONDOWN:	// left mouse button down event
		// display pixel value at (x,y)
		cout << "at (" << x << ", " << y << "), the pixel value is: " <<
			static_cast<int> (im->at<uchar>(Point(x, y))) << endl;
		break;
	}
}


