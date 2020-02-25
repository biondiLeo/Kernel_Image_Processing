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
#include "Convolution.h"

template <typename T>
class KipTemplate {
public:
	KipTemplate(Image s, float* k) : src(s), kernel(k) {};
	Image process();

private:
	Image src;
	float* kernel;
};


//gaussian blur -- sharpen -- box blur 
template<typename T>
Image KipTemplate<T>::process() {
	array<Mat, 3> bgr;
	bgr = src.getBGRChannels();
	array<Mat, 3> dstbgr;
	for (int i = 0; i < src.getChannels(); ++i) {
		dstbgr[i] = Mat::zeros(Size(src.getWidth(), src.getHeight()), CV_8UC1);
		Convolution::convolutionProcess(bgr[i], dstbgr[i], kernel);
	}
	Image dst = Image(dstbgr);
	return dst;
}

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


//EdegeDetection -- Emboss 
template <>
class KipTemplate<EdgeDetection>
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
		Convolution::convolutionProcess(src_gray->getPixels(), dst.getPixels(), kernel);
		delete src_gray;
		return dst;
	}
private:
	Image src;
	float* kernel;
};

template<>
class KipTemplate<Emboss>
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
		Convolution::convolutionProcess(src_gray->getPixels(), dst.getPixels(), kernel);
		delete src_gray;
		return dst;
	}
private:
	Image src;
	float* kernel;
};


#endif // !KIPTEMPLATE_H

