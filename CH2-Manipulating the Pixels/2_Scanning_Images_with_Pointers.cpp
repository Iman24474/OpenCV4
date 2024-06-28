#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>


void colorReduce(cv::Mat image, int div = 64);
void colorReduceMod(cv::Mat image, int div = 64);
void colorReduceBitWise(cv::Mat image, int div = 64);

void colorReduce(const cv::Mat& inputImage, cv::Mat& outputImage, int div = 64);

int main()
{
	//	Reducing the number of colors in an image

	//	For an image, the size of a pixel element is given by the 'elemsize()' method.
	//		Ex: For a three-channel short integer matrix (CV_16SC3), elemsize will return 6
	//	Number of channels in the image is given by the 'nchannels()' method.
	//		Ex: nchannel is 1 for gray-level image, and 3 for a color image
	//	The 'total()' method returns the total number of pixels in the matrix.
	
	//////////////////// 1 ////////////////////

	//	In-place transformation

	//	Read the image
	cv::Mat image = cv::imread("images/boldt.jpg");

	cv::imshow("Then", image);

	// Process the image
	colorReduce(image, 64);

	cv::imshow("Now", image);
	cv::waitKey(0);

	//////////////////// 2 ////////////////////

	// Having input and output arguments
	
	// Read the image
	cv::Mat image1 = cv::imread("images/boldt.jpg");
	
	// Easiest way to create an identical deep copy of an image is to call the 'clone()' method.
	cv::Mat imageClone = image1.clone();

	// Process the clone (Original image remains untouched)
	colorReduce(imageClone);

	cv::imshow("Original Image", image1);
	cv::imshow("Cloned Image", imageClone);
	cv::waitKey(0);

	//////////////////// 3 ////////////////////
	
	// Option to either use or not use in-place processing
	
	cv::Mat result;
	colorReduce(image1, result);

	cv::imshow("Image1", image1);
	cv::imshow("Result", result);

	
	// When in-place processing is preferred, the same image is specified as the input and output
	colorReduce(image1, image1);

	cv::imshow("In-place", image1);
	cv::waitKey(0);


	

}

void colorReduce(cv::Mat image, int div)
{
	// Number of pixel values per row 
	int nc = image.cols * image.channels();

	//Scanning rows, getting the pointer of the row image data
	for (int j=0; j < image.rows; j++)
	{
		// get the address of row j
		uchar* data = image.ptr<uchar>(j);

		// applies the reduction of color to every column of the row pointer
		for (int i = 0; i < nc; i++)
		{
			// process each pixel
			data[i] = data[i] / div * div + div / 2;
			
		}

		// could have equivalently used the pointer arithmetic to move from
			//	column to column
			// 
			//	*data = *data / div * div + div / 2;
			//	data++;
	}

}

//	The inputImage is passed as a const reference, which means that this image will not be modified by the function.
//	The outputImage is passed as a reference so that the calling function will see the output argument modified by this call.
void colorReduce(const cv::Mat &inputImage, cv::Mat &outputImage, int div)
{
	int nl = inputImage.rows; // number of lines
	int nc = inputImage.cols * inputImage.channels(); // Number of pixel values per row 

	// allocate output image if necessary
	//		The key here is first to verify whether the output image has an allocated data buffer with 
	//		a size and pixel type that matches one of the input images.
	//		This check is encapsulated inside the 'create()' method.
	//		If, by chance, the matrix already has the size and type specified, then no operation is performed and
	//			the method simply returns without touching the instance.
	outputImage.create(inputImage.rows, inputImage.cols, inputImage.type());

	for (int j = 0; j < nl; j++)
	{
		// get the addresses of input and output row j
		const uchar* data_in = inputImage.ptr<uchar>(j);
		uchar* data_out = outputImage.ptr<uchar>(j);

		for (int i = 0; i < nc; i++)
		{
			data_out[i] = data_in[i] / div * div + div / 2;
		}
	}
}

// Other color reduction formulas

void colorReduceMod(cv::Mat image, int div)
{
	int nc = image.cols * image.channels();

	for (int j = 0; j < image.rows; j++)
	{
		// get the address of row j
		uchar* data = image.ptr<uchar>(j);

		for (int i = 0; i < nc; i++)
		{
			// process each pixel using modulo operator that brings us to the
			//		nearest multiple of div (the per-channel reduction factor)
			data[i] = data[i] - data[i] % div + div / 2;

		}
	}
}

void colorReduceBitWise(cv::Mat image, int div )
{
	int nc = image.cols * image.channels();

	for (int j = 0; j < image.rows; j++)
	{
		// get the address of row j
		uchar* data = image.ptr<uchar>(j);

		for (int i = 0; i < nc; i++)
		{
			// process each pixel using bitwise operators. 
			//	If we restrict the reduction factor to a power of 2, that is, div = pow(2,n)
			//	then masking the first n bits of the pixel value would give us the nearest
			//	lower multiple of div
			
			// mask used to round the pixel value
			uchar mask = 0xFF << nc;	// e.g. for div = 16, mask = 0xF0
			// color reduction
			*data &= mask; // masking
			*data++ += div >> 1; // add div/2

		}
	}
}

