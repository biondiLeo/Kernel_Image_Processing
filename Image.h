/*
.
.  Kernel Image Processing
.
.  Author: Leonardo Biondi
.
*/

#ifndef IMAGE_H
#define IMAGE_H

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <array>

using namespace cv;
using namespace std;

class Image {
public: 

	// constructors
	Image();

	Image(const Image& src);

	explicit Image(array<Mat, 3> ch);
	
	explicit Image(Mat pix);

	// GET methods
	uchar getPixel(int i, int j) const;
	
	array<Mat, 3> getBGRChannels() const;

	Mat getPixels() const;

	int getWidth() const {
		return width;
	}

	int getHeight() const {
		return height;
	}

	int getChannels() const {
		return channels;
	}

	// SET methods
	void setPixel(int i, int j, int value);

	void setWidth(int width) {
		this->width = width;
	}

	void setHeight(int height) {
		this->height = height;
	}

	void setChannels(int chanels) {
		this->channels = chanels;
	}

	// other methods
	bool compareImages(Image img);

	Image* ConvertRGB2BW(Image * src);

	Image ConvertColor(Image src);

	void Load(const String &path);

	void Save(const String &name);

	void Show(const String &imName);

	// destructor
	~Image() {
		pixels.release();
	}


private:
	int width = 0;
	int height = 0;
	Mat pixels;
	int channels = 1;

};


#endif // !IMAGE_H