//
// pch.cpp
// Include the standard header and generate the precompiled header.
//
#include "pch.h"

#include "Image.h"
#include "Kernel.h"
#include "KipTemplate.h"
#include "Convolution.h"
#include "Image.cpp"
#include "Convolution.cpp"

//Test dimensions
TEST(Image, Test_Dimensions) {
	Image img;
	img.setWidth(20);
	img.setHeight(20);

	EXPECT_EQ(20, img.getWidth());
	EXPECT_EQ(20, img.getHeight());
}

//Test channels
TEST(Image, Test_Channels) {
	Image img;
	img.setChannels(1);

<<<<<<< HEAD
	EXPECT_EQ(1, img.getChannels());
}

//Test pixel
TEST(Image, Test_Pixel)
{
	Image img;
	string imageName("mypgm.pgm");
	img.Load(imageName);

	EXPECT_EQ(1, img.getPixel(0, 0));
	EXPECT_EQ(1, img.getPixel(1, 1));
=======
	EXPECT_EQ(1,img.getChannels());
>>>>>>> 79e62408098e0c9aa7e51cf5962ed7eff25fc5b3
}

//Test compare between two images
TEST(Image, Test_Compare) {
	Image img;
	string imageName("sheldonCooper.pgm");
	img.Load(imageName);

	Image imgGIMP;
	string imageGIMP_Name("sheldonCooper.pgm");
	imgGIMP.Load(imageGIMP_Name);

	bool result = img.compareImages(img, imgGIMP);

	EXPECT_TRUE(result);
}

<<<<<<< HEAD
//Test load and save 
=======
>>>>>>> 79e62408098e0c9aa7e51cf5962ed7eff25fc5b3
TEST(Image, Test_Load_AND_Save)
{
	Image img1;
	string image1_Name("lena.ppm");
	img1.Load(image1_Name);
	img1.Save("lena_TestLoad.ppm");

	Image img2;
	string image2_Name("lena_TestLoad.ppm");
	img2.Load(image2_Name);

<<<<<<< HEAD
=======
	//compare between two images
>>>>>>> 79e62408098e0c9aa7e51cf5962ed7eff25fc5b3
	bool result = img1.compareImages(img1, img2);

	EXPECT_TRUE(result);
}

<<<<<<< HEAD
//Test gaussian blur process
TEST(Image, Test_GaussianBlur) {
	Image dst;
	Image img;
	string imageName("old_man.pgm");
	img.Load(imageName);
=======
>>>>>>> 79e62408098e0c9aa7e51cf5962ed7eff25fc5b3

	Image imgGIMP;
	string imageGIMP_Name("old_man_GaussianBlur.pgm");
	imgGIMP.Load(imageGIMP_Name);
	Image dstGIMP = dstGIMP.ConvertColor(imgGIMP);

	Gaussian_Blur* gb = new Gaussian_Blur();
	KipTemplate<Gaussian_Blur>* tmpGb = new KipTemplate<Gaussian_Blur>(img, gb->getKernel());
	dst = tmpGb->process();

	bool result = dst.compareImages(dst, dstGIMP);

	EXPECT_TRUE(result);
}

//Test sobel edge process
TEST(Image, Test_SobelEdge) {
	Image dst;
	Image img;
	string imageName("old_man.pgm");
	img.Load(imageName);

	Image imgGIMP;
	string imageGIMP_Name("old_man_SobelEdge.pgm");
	imgGIMP.Load(imageGIMP_Name);
	Image dstGIMP = dstGIMP.ConvertColor(imgGIMP);

	SobelEdge* se = new SobelEdge();
	KipTemplate<SobelEdge>* tmpGb = new KipTemplate<SobelEdge>(img, se->getGx(), se->getGy());
	dst = tmpGb->process();

	bool result = dst.compareImages(dst, dstGIMP);

	EXPECT_TRUE(result);
}

//Test sharpen process
TEST(Image, Test_Sharpen) {
	Image dst;
	Image img;
	string imageName("old_man.pgm");
	img.Load(imageName);

	Image imgGIMP;
	string imageGIMP_Name("old_man_Sharpen.pgm");
	imgGIMP.Load(imageGIMP_Name);
	Image dstGIMP = dstGIMP.ConvertColor(imgGIMP);

	Sharpen* s = new Sharpen();
	KipTemplate<Sharpen>* tmpS = new KipTemplate<Sharpen>(img, s->getKernel());
	dst = tmpS->process();

	bool result = dst.compareImages(dst, dstGIMP);

	EXPECT_TRUE(result);
}

//Test edge detection process
TEST(Image, Test_EdgeDetection) {
	Image dst;
	Image img;
	string imageName("old_man.pgm");
	img.Load(imageName);

	Image imgGIMP;
	string imageGIMP_Name("old_man_EdgeDetection.pgm");
	imgGIMP.Load(imageGIMP_Name);
	Image dstGIMP = dstGIMP.ConvertColor(imgGIMP);

	EdgeDetection* ed = new EdgeDetection();
	KipTemplate<EdgeDetection>* tmpS = new KipTemplate<EdgeDetection>(img, ed->getKernel());
	dst = tmpS->process();

	bool result = dst.compareImages(dst, dstGIMP);

	EXPECT_TRUE(result);
}

//Test Emboss
TEST(Image, Test_Emboss) {
	Image dst;
	Image img;
	string imageName("old_man.pgm");
	img.Load(imageName);

	Image imgGIMP;
	string imageGIMP_Name("old_man_Emboss.pgm");
	imgGIMP.Load(imageGIMP_Name);
	Image dstGIMP = dstGIMP.ConvertColor(imgGIMP);

	Emboss* ess = new Emboss();
	KipTemplate<Emboss>* tmpS = new KipTemplate<Emboss>(img, ess->getKernel());
	dst = tmpS->process();

	bool result = dst.compareImages(dst, dstGIMP);

	EXPECT_TRUE(result);
}






