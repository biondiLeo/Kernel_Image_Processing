//
// pch.cpp
// Include the standard header and generate the precompiled header.
//
#include "pch.h"

#include "Image.h"


TEST(Image, TestDimensions) {
	Image i;
	i.setWidth(20);
	i.setHeight(20);
	EXPECT_EQ(20, i.getWidth());
	EXPECT_EQ(20, i.getHeight());
}

TEST(Image, TestChannels) {
	Image i;
	i.setChannels(1);
	EXPECT_EQ(1,i.getChannels());
}
