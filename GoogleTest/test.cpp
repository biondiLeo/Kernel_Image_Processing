/*
.
.  Kernel Image Processing - GoogleTest
.
.  Author: Leonardo Biondi
.
*/

#include "gtest/gtest.h"
#include "pch.h"

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}