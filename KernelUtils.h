#ifndef KERNELUTILS_H
#define KERNELUTILS_H

#include "Image.h"
class KernelUtils 
{
public:
	KernelUtils() = default;
	static void noBorderProcessing(Mat src, Mat dst, float Kernel[]);
};
#endif // !KERNELUTILS_H

