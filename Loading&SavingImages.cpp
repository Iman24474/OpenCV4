#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	// #1 Create an empty image object
	Mat image;
	// #2 Read an image from the file
	image = imread("images/puppy.bmp");
	// #3 Error handling
	if (image.empty())
	{
		cout << "No image is found!" << endl;
	}
	// #4 Show the image
	imshow("Original Photo", image);

	// #5 Apply some processing to the image
	Mat result; // Create another empty image
	flip(image, result, 1); // Positive for horizontal
							// 0 for vertical
							// Negative for both

	// Displaying the result in a new window
	imshow("Output Image", result);

	// #6 Add a function to wait for a user keypress before ending the program
	waitKey(0); // 0 to indefinitely wait for a key pressed
				// Specifying a positive value will wait for the given amount of msec

	// #7 Save the processed image on the disk
	imwrite("output.bmp", result); // save result
								  // The file extension determines which codec will be used to save the image.
	return 0;
}
