/*
.
.  Kernel Image Processing
.
.  Author: Leonardo Biondi
.
*/

#ifndef CONVOLUTION_H
#define CONVOLUTION_H

#include "Image.h"
class Convolution
{
public:
	Convolution() = default;
	static void convolutionProcess(Mat src, Mat dst, float Kernel[]);
};
#endif // !CONVOLUTION_H

