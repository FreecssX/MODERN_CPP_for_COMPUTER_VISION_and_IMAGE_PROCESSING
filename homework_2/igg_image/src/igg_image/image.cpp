#include "image.h"
#include <iostream>
#include <cmath>
using namespace igg;
//using namespace io_tools;
Image::Image(): rows_{0}, cols_{0} {}
Image::Image(int rows, int cols) {
	if(rows <= 0 || cols <= 0);
	else rows_ = rows, cols_ = cols;
	data_ = std::vector<int>(rows*cols, 0);
}

const int& Image::rows() const {return rows_;}
const int& Image::cols() const {return cols_;}

int& Image::at(int row, int col) {return data_[row*cols_ + col];}

bool Image::FillFromPgm(const std::string& file_name) {
	bool flag = false;
	io_tools::ImageData id = io_tools::ReadFromPgm(file_name);
	if(id.data.size() > 0) flag = true;
	rows_ = id.rows;
	cols_ = id.cols;
	data_ = id.data;
	return flag;
}

void Image::WriteToPgm (const std::string& file_name) const {
	io_tools::ImageData id = {rows_, cols_, max_val_, data_};
	io_tools::WriteToPgm(id, file_name);
}

std::vector<float> Image::ComputeHistogram(int bins) const {
	std::vector<float> ret(bins);
	int sum = 0;
	for(int i = 0; i < rows_; i += 1) {
		//std::cout<<std::endl;
		for(int j = 0; j < cols_; j += 1) {
			//std::cout<<data_[cols_ * i + j]<<" ";
			int index = data_[cols_ * i + j] * bins % 255 == 0? floor(data_[cols_ * i + j] * bins / 255) - 1: floor(data_[cols_ * i + j] * bins / 255);
			
			//std::cout<<index<<" ";
			ret[index] += 1;
			sum += 1;
		}
	}
	for(int i = 0; i < bins; i += 1) {
		ret[i] /= sum;
		std::cout<<ret[i]<< " "<<std::endl;
	}
	return ret;
}
void Image::DownScale(int scale) {
	int new_rows_ = rows_ / scale;
	int new_cols_ = cols_ / scale;
	if(new_rows_ == 0) new_rows_ = 1;
	if(new_cols_ == 0) new_cols_ = 1;
	std::vector<int> new_data_(new_rows_ * new_cols_);
	int index = 0;
	for(int i = 0; i < rows_; i += scale) {
		for(int j = 0; j < cols_; j += scale) {
			if(index < new_rows_ * new_cols_) new_data_[(i / scale) * new_cols_ + j / scale] = data_[i * cols_ + j];
			index += 1;
		}
	}
	rows_ = new_rows_;
	cols_ = new_cols_;
	data_ = new_data_;
}

void Image::UpScale(int scale) {
	int new_rows_ = rows_ * scale;
	int new_cols_ = cols_ * scale;
	std::vector<int> new_data_(new_rows_ * new_cols_);
	for(int i = 0; i < new_rows_; i += 1) {
		for(int j = 0; j < new_cols_; j += 1) {
			int srcX = floor(i * (float(rows_) / new_rows_));
			int srcY = floor(j * (float(cols_) / new_cols_));
			new_data_[new_cols_ * i + j] = data_[srcX * cols_ + srcY];
		}
	}
	data_ = new_data_;
	rows_ = new_rows_;
	cols_ = new_cols_;
}

