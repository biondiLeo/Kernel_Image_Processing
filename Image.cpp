/*
.
.  Kernel Image Processing
.
.  Author: Leonardo Biondi
.
*/

#include <iostream>
#include <stdlib.h>
#include "Image.h"

//Load an image
void Image::Load(const String &path)
{
	Mat temp = imread(path, IMREAD_COLOR);
	if (temp.empty())
	{
		throw invalid_argument("Couldn't find any image, please check the path");
	}
	pixels = imread(path, IMREAD_COLOR);
	channels = pixels.channels();
	width = pixels.cols;
	height = pixels.rows;
}

//Save an image
void Image::Save(const String &name)
{
	imwrite(name, this->pixels);
}

//Get pixel in the chosen position 
uchar Image::getPixel(int i, int j)
{
	if (i<0 || i>height || j<0 || j>width)
		throw out_of_range("Index i=" + to_string(i) + ", j=" + to_string(j) + " out of bound");
	else
		return pixels.at<uchar>(i, j);
}

//Get bgr channels
array<Mat, 3> Image::getBGRChannels()
{
	array<Mat, 3> bgr;
	if (channels > 1) {
		split(pixels, bgr);
	}
	else {
		bgr[0] = pixels;
		bgr[1] = Mat::zeros(Size(width, height), CV_8UC1);
		bgr[2] = Mat::zeros(Size(width, height), CV_8UC1);
	}
	return bgr;
}

//Show an image
void Image::Show(const String &imName)
{
	imshow(imName, pixels);
}

//Convert RGB to black and white
Image* Image::ConvertRGB2BW(Image *src)
{
	Mat src_gray;
	cvtColor(src->pixels, src_gray, COLOR_BGR2GRAY);
	return new Image(src_gray);
}

//Set pixel in the chosen position
void Image::setPixel(int i, int j, int value)
{
	this->pixels.at<uchar>(i, j) = value;
}

//Get all pixels
Mat Image::getPixels()
{
	return this->pixels;
}

//Compare two images
bool Image::compareImages(Image img1, Image img2)
{
	int check = 0;
	if (img1.getHeight() != img2.getHeight() || img1.getWidth() != img2.getWidth())
	{
		return false;
	}
	else
	{
		for (int i = 0; i < img1.getHeight(); i++)
		{
			for (int j = 0; j < img1.getWidth(); j++)
			{
				if (img1.getPixel(i, j) != img2.getPixel(i, j))
				{
					check = -1;
				}
			}
		}

		if (check == 0)
			return true;
		else
			return false;

	}
}

//Convert the uploaded image to a gray scale
Image Image::ConvertColor(Image src)
{
	Image* ptr_src;
	ptr_src = src.ConvertRGB2BW(&src);
	Image dst = Image(*ptr_src);

	return dst;
}