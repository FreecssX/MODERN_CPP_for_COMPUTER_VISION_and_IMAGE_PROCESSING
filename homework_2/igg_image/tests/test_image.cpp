#include "image.h"
#include <gtest/gtest.h>
#include <iostream>
TEST(ImageTest, initialize) {
	igg::Image* img = new igg::Image();
	ASSERT_TRUE(img != NULL);
	igg::Image* img1 = new igg::Image(3, 4);
	ASSERT_TRUE(img1 != NULL);
	int rows = img1->rows();
	int cols = img1->cols();
	EXPECT_EQ(rows, 3);
	EXPECT_EQ(cols, 4); 
	int& val = img1->at(1, 2);
	EXPECT_EQ(val, 0);
	val = 7;
	int val_new = img1->at(1, 2);
	EXPECT_EQ(val_new, 7);
	
}

TEST(ImageTest, read_write) {
	std::string file_name = "../../data/lena.ascii.pgm";
	igg::Image* img = new igg::Image();
	bool is_read = img->FillFromPgm(file_name);
	ASSERT_TRUE(is_read);
	int rows = img->rows();
	int cols = img->cols();
	EXPECT_EQ(rows, 512);
	EXPECT_EQ(cols, 512);
	img->WriteToPgm("../../data/lena_copy.ascii.pgm"); //you can find a copy of lena inside data folder
}

TEST(ImageTest, histogram) {
	igg::Image* img = new igg::Image(4, 4);
	int rows = img->rows();
	for(int i = 0; i < 4; i += 1) {
		for(int j = 0; j < 4; j += 1) {
			img->at(i, j) = 16 * (i * rows + j + 1) - 1;
		}
	}
	//to illustrate the image:
	// [15,  31,  47,  63
	//  79,  95,  111, 127
	//  143, 159, 175, 191
	//  207, 223, 239, 255]
	std::vector<float> result = {0.25, 0.25, 0.25, 0.25};
	std::vector<float> test = img->ComputeHistogram(4);
	for(int i = 0; i < 4; i += 1) {
		EXPECT_FLOAT_EQ(result[i], test[i]);
	}
}

TEST(ImageTest, downscale) {
	igg::Image* img = new igg::Image(4, 4);
	int rows = img->rows();
	for(int i = 0; i < 4; i += 1) {
		for(int j = 0; j < 4; j += 1) {
			img->at(i, j) = 16 * (i * rows + j + 1) - 1;
		}
	}
	std::vector<int> result = {15, 47, 143, 175};
	img->DownScale(2);
	rows = img->rows();
	int cols = img->cols();
	for(int i = 0; i < rows; i += 1) {
		for(int j = 0; j < cols; j += 1) {
			EXPECT_EQ(result[i * cols + j], img->at(i, j));
		}
	}
	std::string file_name = "../../data/lena.ascii.pgm";
	igg::Image* img1 = new igg::Image();
	img1->FillFromPgm(file_name);
    img1->DownScale(2);
	img1->WriteToPgm("../../data/lena_downscale.ascii.pgm"); //you can find a downscaled picture inside the data folder
}

TEST(ImageTest, upscale) {
    igg::Image* img0 = new igg::Image(2, 2);
	img0->at(0, 0) = 0;
	img0->at(0, 1) = 1;
	img0->at(1, 0) = 2;
	img0->at(1, 1) = 3;
	std::vector<std::vector<int>> result(4, std::vector<int>(4));
	for(int i = 0; i < 4; i += 1) {
		for(int j = 0; j < 4; j += 1) {
			result[i][j] = img0->at(i / 2, j / 2);
		}
	}
	img0->UpScale(2);
	for(int i = 0; i < 4; i += 1) {
		for(int j = 0; j < 4; j += 1) {
			EXPECT_EQ(result[i][j], img0->at(i, j));
		}
	}
	std::string file_name = "../../data/lena.ascii.pgm";
	igg::Image* img = new igg::Image();
	img->FillFromPgm(file_name);
	img->UpScale(2);
	img->WriteToPgm("../../data/lena_upscale.ascii.pgm"); // you can find a upscaled picture inside the data folder
}
int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
