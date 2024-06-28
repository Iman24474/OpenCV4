#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>


void salt(cv::Mat image, int n);

int main()
{

	// Read an image
	cv::Mat image = cv::imread("images/boldt.jpg");
	
	// Call the salt function to add noise
	salt(image, 3000);

	cv::imshow("Image", image);
	cv::waitKey(0);

	return 0;
}

void salt(cv::Mat image, int n)
{
	int i, j; // x and y
	for (int k = 0; k < n; k++)
	{
		// Generate two random image positions using 'std::rand()'
		//		The 'std::rand()' returns a value between 0 and RAND_MAX
		//		We apply a module % to it with cols and rows of the image 
		//		to return only values between 0 and the width and height.
		i = std::rand() % image.cols;
		j = std::rand() % image.rows;

		// Use the 'type()' method to distinguish between the two cases of
		//	gray-level and color images.
		//	In the case of a gray-level image, the number 255 is assigned to the 
		//	single 8-bit value using the Mat function 'at<type>(y,x)'
		if (image.type() == CV_8UC1) // gray-level image
		{
			image.at<uchar>(j, i) = 255;
		}

		// For a color image, you need to assign 255 to the three primary color
		//	channels in order to obtain a white pixel.
		//	To access each channel, we can use the array access [nchannel] where
		//	nchannel is the number of channels in the BGR format:
		//		-> 0 is blue
		//		-> 1 is green
		//		-> 2 is red
		else if (image.type() == CV_8UC3) // color image
		{
			// cv::Vect3b is a vector of three unsigned characters
			// 'cv::Vec<T,N>' template class, where 'T' is the type and 'N' is
			//		number of vector elements.
			image.at<cv::Vec3b>(j, i)[0] = 255;
			image.at<cv::Vec3b>(j, i)[1] = 255;
			image.at<cv::Vec3b>(j, i)[2] = 255;
		}
	}
}