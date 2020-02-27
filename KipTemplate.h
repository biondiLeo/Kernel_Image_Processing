/*
.
.  Kernel Image Processing
.
.  Author: Leonardo Biondi
.
*/

#ifndef KIPTEMPLATE_H
#define KIPTEMPLATE_H

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "Image.h"
#include "Kernel.h"

template<class T>
class KipOperation
{
protected:
	void convolution(Mat src, Mat dst, float Kernel[])
	{
		float sum;
		for (int i = 1; i < src.rows - 1; i++) {
			for (int j = 1; j < src.cols - 1; j++) {
				sum = 0.0;
				for (int k = -1; k <= 1; k++) {
					for (int l = -1; l <= 1; l++) {
						sum += src.at<uchar>(i + k, j + l) * Kernel[(k + 1) * 3 + (l + 1)];
					}
				}
				sum > 255 ? sum = 255 : sum;
				sum < 0 ? sum = 0 : sum;
				dst.at<uchar>(i, j) = sum;
			}
		}
	}
};

template <typename T>
class KipTemplate {
public:
	KipTemplate(Image s, float* k) : src(s), kernel(k) {};
	Image process();

private:
	Image src;
	float* kernel;
};



/*
. Identical convolution process for the following kernels:
.	- Edge Detection
.	- Emboss
*/
template <>
class KipTemplate<EdgeDetection> : public KipOperation<EdgeDetection>
{
public:
	KipTemplate(Image s, float* k) : src(s), kernel(k) {};
	Image process()
	{
		Image* src_gray = nullptr;
		if (src.getChannels() > 1)
			src_gray = src.ConvertRGB2BW(&src);
		else
			*src_gray = Image(src);
		Image dst = Image(*src_gray);
		KipOperation<EdgeDetection>::convolution(src_gray->getPixels(), dst.getPixels(), kernel);

		delete src_gray;
		return dst;
	}
private:
	Image src;
	float* kernel;
};


template<>
class KipTemplate<Emboss> : public KipOperation<Emboss>
{
public:

	KipTemplate(Image s, float* k) : src(s), kernel(k) {};
	Image process()
	{
		Image* src_gray = nullptr;
		if (src.getChannels() > 1)
			src_gray = src.ConvertRGB2BW(&src);
		else
			*src_gray = Image(src);
		Image dst = Image(*src_gray);
		KipOperation<Emboss>::convolution(src_gray->getPixels(), dst.getPixels(), kernel);
		delete src_gray;
		return dst;
	}
private:
	Image src;
	float* kernel;
};


/*
. Convolution process for the kernel:
.	- Sobel Edge
*/
template <>
class KipTemplate<SobelEdge>
{
public:
	KipTemplate(Image s, float *x, float *y) : src(s), Gx(*reinterpret_cast<float(*)[3][3]> (x)), Gy(*reinterpret_cast<float(*)[3][3]> (y)) {};
	Image process()
	{
		float pixel_x;
		float pixel_y;
		float val;
		Image* src_gray = new Image(src);
		if (src.getChannels() > 1)
			src_gray = src.ConvertRGB2BW(&src);
		Image dst = Image(*src_gray);
		try {
			for (int x = 1; x < src_gray->getHeight() - 2; x++) {
				for (int y = 1; y < src_gray->getWidth() - 2; y++) {
					pixel_x = (Gx[0][0] * src_gray->getPixel(x - 1, y - 1)) + (Gx[0][1] * src_gray->getPixel(x, y - 1)) +
						(Gx[0][2] * src_gray->getPixel(x + 1, y - 1)) +
						(Gx[1][0] * src_gray->getPixel(x - 1, y)) + (Gx[1][1] * src_gray->getPixel(x, y)) +
						(Gx[1][2] * src_gray->getPixel(x + 1, y)) +
						(Gx[2][0] * src_gray->getPixel(x - 1, y + 1)) + (Gx[2][1] * src_gray->getPixel(x, y + 1)) +
						(Gx[2][2] * src_gray->getPixel(x + 1, y + 1));
					pixel_y = (Gy[0][0] * src_gray->getPixel(x - 1, y - 1)) + (Gy[0][1] * src_gray->getPixel(x, y - 1)) +
						(Gy[0][2] * src_gray->getPixel(x + 1, y - 1)) +
						(Gy[1][0] * src_gray->getPixel(x - 1, y)) + (Gy[1][1] * src_gray->getPixel(x, y)) +
						(Gy[1][2] * src_gray->getPixel(x + 1, y)) +
						(Gy[2][0] * src_gray->getPixel(x - 1, y + 1)) + (Gy[2][1] * src_gray->getPixel(x, y + 1)) +
						(Gy[2][2] * src_gray->getPixel(x + 1, y + 1));
					val = (int)sqrt((pixel_x * pixel_x) + (pixel_y * pixel_y));
					dst.setPixel(x, y, val);
				}
			}
		}
		catch (out_of_range &ex) {
			cerr << ex.what() << endl;
		}
		delete src_gray;
		return dst;
	};
private:
	Image src;
	float(*Gx)[3];
	float(*Gy)[3];
};


/*
. Identical convolution process for the following kernels:
.	- Gaussian Blur
.	- Sharpen
.	- Box Blur
*/
template<typename T>
Image KipTemplate<T>::process() {
	array<Mat, 3> bgr;
	bgr = src.getBGRChannels();
	array<Mat, 3> dstbgr;
	for (int z = 0; z < src.getChannels(); ++z) {
		dstbgr[z] = Mat::zeros(Size(src.getWidth(), src.getHeight()), CV_8UC1);
		float sum;
		for (int i = 1; i < bgr[z].rows - 1; i++) {
			for (int j = 1; j < bgr[z].cols - 1; j++) {
				sum = 0.0;
				for (int k = -1; k <= 1; k++) {
					for (int l = -1; l <= 1; l++) {
						sum += bgr[z].at<uchar>(i + k, j + l) * kernel[(k + 1) * 3 + (l + 1)];
					}
				}
				if (sum > 255)
					sum = 255;
				else if (sum < 0)
					sum = 0;
				dstbgr[z].at<uchar>(i, j) = sum;
			}
		}
	}
	Image dst = Image(dstbgr);
	return dst;
}


#endif // !KIPTEMPLATE_H


