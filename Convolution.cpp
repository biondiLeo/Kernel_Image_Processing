/*
.
.  Kernel Image Processing
.
.  Author: Leonardo Biondi
.
*/

#include <iostream>
#include "Convolution.h"

//Mathematical process of the convolution between image and kernel
void Convolution::convolutionProcess(Mat src, Mat dst, float Kernel[])
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