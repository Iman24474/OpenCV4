#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

// Create a function that generates a new gray image
//	with a defualt value for all its pixels 
cv::Mat function()
{
	// create an image
	cv::Mat ima(500, 500, CV_8U, 50);
	return ima;
}

int main()
{

	//////////////////// 1 ////////////////////

	// Create a new image made of 240 rows and 320 columns, a channel, and a defualt value
	//		CV_8U: Corresponds to 1-byte pixel images.
	//			-> The letter 'U' means it's unsigned. (You can declare signed numbers
	//					by using the letter 'S').
	//			-> For a color image, you would specify three channels 'CV_U8C3'
	//			-> You can declare integers (signed or unsigned) of size 16 and 32 like 'CV_16SC3'
	//			-> YOu also have access to 32-bit and 64 bit floating point numbers like 'CV_32F'
	cv::Mat image1(240, 320, CV_8U, 100);
	
	cv::imshow("Image", image1); // show the image
	cv::waitKey(0); // wait for a key pressd

	//////////////////// 2 ////////////////////
	// The data block of an image can always be allocated or reallocated using 'create' method.

	// Re-allocate a new image
	image1.create(200, 200, CV_8U);
	image1 = 200; // set the value

	cv::imshow("Image", image1); // show the image
	cv::waitKey(0);

	//////////////////// 3 ////////////////////

	// Create a red color image
	//	channel order is BGR
	//	The 'cv::Scalar' structure is generally used to hold one value or three values.
	//		-> The initialization of the grey-level image could also have been done using
	//			cv::Scalar(100)
	cv::Mat image2(240, 320, CV_8UC3, cv::Scalar(0, 0, 255));

	//	or:
	/*
	* 
	cv::Mat image2(cv::Size(320, 240), CV_8UC3); // cv::Size() structure contains the height and Width
	image2 = cv::Scalar(0, 0, 255);

	*/

	cv::imshow("Image", image2);
	cv::waitKey(0);

	//////////////////// 4 ////////////////////

	// Read an image
	cv::Mat image3 = cv::imread("images/puppy.bmp");

	// All these images point to the same data block
	//		Any transformation applied to one of the following images will affect the other images
	cv::Mat image4(image3);
	image1 = image3;

	// These images are new copies of the source image
	//		If you wish to create a deep copy of the content of an image, use 'copyTo()' or 'clone()' methods.
	image3.copyTo(image2);
	cv::Mat image5 = image3.clone();

	//////////////////// 5 ////////////////////

	// Transform the image for testing
	cv::flip(image3, image3, 1);

	// Check which images have been affected by the processing
	cv::imshow("Image 3", image3);
	cv::imshow("Image 1", image1); // like image 3
	cv::imshow("Image 2", image2);
	cv::imshow("Image 4", image4); // Like image 3
	cv::imshow("Image 5", image5);
	cv::waitKey(0);

	//////////////////// 6 ////////////////////

	// Get a gray-level image from a function created above to generate a new gray matrix
	cv::Mat gray = function();

	cv::imshow("Image", gray);
	cv::waitKey(0);

	//////////////////// 7 ////////////////////

	// Read the image in gray scale
	image1 = cv::imread("images/puppy.bmp", cv::ImreadModes::IMREAD_GRAYSCALE);

	// If you need to copy an image into another image that deosn't necessarilly have the same
	//	data type, you have to use the 'convertTo' method.
	//		Below, the source image is coppied into a floating-point image. The method includes two optional parameters:
	//		-> Scaling factor
	//		-> Offset
	//		*** Note: Both the images must have the same number of channels.
	image1.convertTo(image2, CV_32F, 1 / 255.0, 0.0);

	cv::imshow("Image", image2);
	cv::waitKey(0);

	return 0;
}

