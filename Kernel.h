/*
.
.  Kernel Image Processing
.
.  Author: Leonardo Biondi
.
*/

#ifndef KERNEL_H
#define KERNEL_H

#include "Image.h"
#include "Convolution.h"

using namespace std;

class Gaussian_Blur {
public:
	Gaussian_Blur() = default;
	float* getKernel() { return Kernel; };
private:
	float Kernel[9] = {
		1 / 16.0, 2 / 16.0, 1 / 16.0,
		2 / 16.0, 4 / 16.0, 2 / 16.0,
		1 / 16.0, 2 / 16.0, 1 / 16.0
	};
};

class Sharpen {
public:
	Sharpen() = default;
	float* getKernel() { return Kernel; };
private:
	float Kernel[9] = {
		0, -1, 0,
		-1, 5, -1,
		0, -1, 0
	};

};

class SobelEdge {
public:
	SobelEdge() = default;
	float* getGx() { return (*Gx); };
	float* getGy() { return (*Gy); };
private:
	float Gx[3][3] = {
		{ -1, 0, 1 },
		{ -2, 0, 2 },
		{ -1, 0, 1 }
	};
	float Gy[3][3] = {
		{ -1, -2, -1 },
		{ 0, 0, 0 },
		{ 1, 2, 1 }
	};
};

class EdgeDetection {
public:
	EdgeDetection() = default;
	float* getKernel() { return Kernel; };
private:
	float Kernel[9] = {
		-1, -1, -1,
		-1, 8, -1,
		-1, -1, -1
	};
};

class Emboss {
public:
	Emboss() = default;
	float* getKernel() { return Kernel; };
private:
	float Kernel[9] = {
		-2, -1, 0,
		-1, 1, 1,
		0, 1, 2
	};
};
#endif // !KERNEL_H