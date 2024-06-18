#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>


int main()
{
	//////////////////// 1 ////////////////////
	// 
	// Read images from the file
	cv::Mat image = cv::imread("images/puppy.bmp");
	cv::Mat image2 = cv::imread("images/puppy.bmp");
	cv::Mat logo = cv::imread("images/smalllogo.png");

	//////////////////// 2 ////////////////////

	// Define the Region of Interest (ROI)
	cv::Rect myRoi = cv::Rect(image.cols - logo.cols, // ROI coordinates of top-left corner
							image.rows - logo.rows,
							logo.cols, // width of rect
							logo.rows); // height of rect


	//////////////////// 3 ////////////////////
	
	// Define image ROI at image bottom-right
	//	Once the ROI is defined, we can create a new mat applying 
	//	the ROI to another mat
	//		*** ROI is a cv::Mat object that points to the same data buffer 
	//			as its parent image and has a header that specifies its coordinates
	//	Any Transformation of ROI will affect the original image in the corresponding area
	//	because the image and ROI share the same image data
	cv::Mat imageROI(image, myRoi);

	// The ROI can also be described using row and column ranges.
	//	A range is a continuous sequence from a start index to an end index (excluding both)
	imageROI = image(cv::Range(image.rows - logo.rows, image.rows),
					cv::Range(image.cols - logo.cols, image.cols));

	// insert logo
	logo.copyTo(imageROI);

	cv::imshow("Image", image);
	cv::waitKey(0);

	//////////////////// 4 ////////////////////

	// Using image masks
	//	A mask is an 8-bit image that should be non-zero at all locations where
	//	you want an operation to be applied. At the pixel locations that correspond to
	//	the zero values of the mask, the image is untouched.

	// Define image ROI at a image bottom-right
	imageROI = image2(cv::Rect(image2.cols - logo.cols,
							image2.rows - logo.rows,
							logo.cols,
							logo.rows));

	// Use the logo as a mask (Must be gray-level)
	//	The background of the logo was black and therefore it had the value 0
	//		*** For gray-level image, 0 corresponds to black and 255 corresponds to white
	cv::Mat mask(logo);

	// Insert by copying only at locations of non-zero mask
	logo.copyTo(imageROI, mask);

	cv::imshow("Image2", image2);
	cv::waitKey(0);


	return 0;
}