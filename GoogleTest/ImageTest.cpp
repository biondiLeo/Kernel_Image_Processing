//
// pch.cpp
// Include the standard header and generate the precompiled header.
//
#include "pch.h"

#include "Image.h"
#include "Kernel.h"
#include "KipTemplate.h"
#include "KernelUtils.h"
#include "Image.cpp"
#include "KernelUtils.cpp"

TEST(Image, Test_Dimensions) {
	Image img;
	img.setWidth(20);
	img.setHeight(20);
	EXPECT_EQ(20, img.getWidth());
	EXPECT_EQ(20, img.getHeight());
}

TEST(Image, Test_Channels) {
	Image img;
	img.setChannels(1);
	EXPECT_EQ(1,img.getChannels());
}

TEST(Image, Test_Compare) {
	Image dst;
	Image img;
	string imageName("sheldonCooper.pgm");
	img.Load(imageName);
	
	Image imgGIMP;
	string imageGIMP_Name("sheldonCooper.pgm");
	imgGIMP.Load(imageGIMP_Name);

	bool result = img.compareImages(img, imgGIMP);
	
	EXPECT_TRUE(result);
	
}


TEST(Image, Test_Emboss) {
	Image dst;
	Image img;
	string imageName("old_man.pgm");
	img.Load(imageName);

	Image imgGIMP;
	string imageGIMP_Name("old_man_Gimp_Emboss.pgm");
	imgGIMP.Load(imageGIMP_Name);

	
	Emboss* ess = new Emboss();
	KipTemplate<Emboss>* tmpS = new KipTemplate<Emboss>(img, ess->getKernel());
	dst = tmpS->process();
	
	bool result = dst.compareImages(dst, imgGIMP);

	EXPECT_TRUE(result);

}
