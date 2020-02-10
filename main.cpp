
#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include <fstream>
#include "Kernel.h"
#include "Image.h"
#include "KipTemplate.h"


using namespace std;
using namespace cv;

int main() {
	cout << endl << "============= IMAGE CONVOLUTION ==============" << endl << endl;

	string imageName("lena.ppm");
	cout << " ...Loading image located at " << imageName << "..." << endl << endl;
	Image img;
	try {
		img.Load(imageName);
	}
	catch (invalid_argument &ex) {
		cout << "Exiting the program" << endl;
		exit(-1);
	}
	int option = -1;
	cout << " Choose which effect you would like to apply:" << endl;
	cout << " 1: Gaussian Blur" << endl;
	cout << " 2: Sobel Edge" << endl;
	cout << " 3: Sharpen" << endl;
	cout << " 4: Edge Detection" << endl;
	cout << " 5: Emboss" << endl << endl;
	cout << " => ";
	cin >> option;

	Image dst;

	while (cin.fail() || option < 0 || option>5) {
		cout << "Not valid, please retry" << endl;
		cin >> option;
	}
	switch (option) {
	case 1:
	{
		Gaussian_Blur* gb = new Gaussian_Blur();
		KipTemplate<Gaussian_Blur>* tmpGb = new KipTemplate<Gaussian_Blur>(img, gb->getKernel());
		dst = tmpGb->process();

		if (dst.getChannels() > 1)
			dst.Save("GaussianBlur.ppm");
		else
			dst.Save("GaussianBlur.pgm");
		break;
	}
	
	case 2:
	{	
		SobelEdge* se = new SobelEdge();
		KipTemplate<SobelEdge>* tmpGb = new KipTemplate<SobelEdge>(img, se->getGx(), se->getGy());  
		dst = tmpGb->process();
	
		dst.Save("SobelEdge.pgm");
		break;
	}
	
	case 3:
	{
		Sharpen* s = new Sharpen();
		KipTemplate<Sharpen>* tmpS = new KipTemplate<Sharpen>(img, s->getKernel());
		dst = tmpS->process();

		if (dst.getChannels() > 1)
			dst.Save("Sharpen.ppm");
		else
			dst.Save("Sharpen.pgm");
		break;
	}
		
	case 4:
	{
		EdgeDetection* ed = new EdgeDetection();
		KipTemplate<EdgeDetection>* tmpS = new KipTemplate<EdgeDetection>(img, ed->getKernel()); 
		dst = tmpS->process();

		dst.Save("EdgeDetection.pgm");
		break;
	}

	case 5:
	{
		Emboss* ess = new Emboss();
		KipTemplate<Emboss>* tmpS = new KipTemplate<Emboss>(img, ess->getKernel());
		dst = tmpS->process();

		if (dst.getChannels() > 1)
			dst.Save("Emboss.ppm");
		else
			dst.Save("Emboss.pgm");
		break;
	}
	
	default:
		exit(-2);
	}

	cout << endl << " ...Display original image and processed image" << endl;
	cout << endl << "==============================================" << endl;
	img.Show("Original Image");
	dst.Show("Processed Image");

	waitKey(0);
	return 0;

}