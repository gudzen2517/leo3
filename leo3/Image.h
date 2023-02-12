#include<iostream>
#include<vector>
#include<iterator>

using namespace std;

template <typename T>
class Image {
private:
	vector<vector<T>> image;
	size_t width, height;
public:

	Image();
	Image(const size_t a_width, const size_t a_height);
	Image(const Image& image_copy);
	~Image();
	T operator()(const size_t a_width, const size_t a_height) const;
	T& operator()(const size_t a_width, const size_t a_height);
	Image operator =(const Image& a_image);
	Image operator *(const Image& a_image) const;
	Image operator +(const Image& a_image) const;
	Image operator *(const T a_b) const;
	Image operator +(const T a_b) const;
	//binaryimage operator !() const;
	bool operator ==(const Image& a_image) const;
	double ratio() const;
	//friend ostream& operator <<(std::ostream& os, const binaryimage& a_image);
	typename vector<vector<T>>::iterator begin()const;
	typename vector<vector<T>>::iterator end() const;
	size_t get_width() const;
	size_t get_height() const;
	void print_im() const;
};



template <typename T>
Image<T>::Image() : image(0), width(0), height(0) {}

template <typename T>
Image<T>::Image(const size_t a_width, const size_t a_height) {
	if (a_width == 0 || a_height == 0) {
		throw std::out_of_range("The number of rows and columns should be >0");
	}
	width = a_width;
	height = a_height;
	for (size_t i = 0; i < width; ++i) {
		image.push_back(vector<T>(height));
	}
}
/*
template <>
Image<char>::Image(const size_t a_width, const size_t a_height) {
	if (a_width == 0 || a_height == 0) {
		throw std::out_of_range("The number of rows and columns should be >0");
	}
	width = a_width;
	height = a_height;
	image = new char* [width];
	for (size_t i = 0; i < width; ++i) {
		image[i] = new char[height];
		for (size_t j = 0; j < height; ++j) {
			image[i][j] = 48;
		}
	}
}*/

template <typename T>
Image<T>::Image(const Image& image_copy) {
	width = image_copy.width;
	height = image_copy.height;
	image.resize(width);
	for (size_t i = 0; i < width; i++)
	{
		for (size_t j = 0; j < height; j++)
		{
			image[i].push_back(image_copy(i,j));
		}
	}
}



template <typename T>
T Image<T>::operator()(const size_t a_width, const size_t a_height) const {
	if (a_width > width || a_height > height)
		throw std::out_of_range("Incorrect coordinates");
	return image[a_width][a_height];
}

template <typename T>
T& Image<T>::operator()(const size_t a_width, const size_t a_height) {
	if (a_width > width || a_height > height)
		throw std::out_of_range("Incorrect coordinates");
	return image[a_width][a_height];
}

template <typename T>
Image<T> Image<T>::operator =(const Image& a_image) {
	width = a_image.width;
	height = a_image.height;
	if (width != a_image.width || height != a_image.height) {
		if (image) {
			image.clear();
		}
		image.resize(width);
	}
	for (size_t i = 0; i < width; i++)
	{
		for (size_t j = 0; j < height; j++)
		{
			image[i].push_back(a_image(i, j));
		}
	}
	return a_image;
}

template <typename T>
Image<T> Image<T>::operator*(const Image& a_image) const {
	size_t x_min = 0, y_min = 0, result_width, result_height;
	if (width > a_image.width) {
		result_width = width;
		x_min = a_image.width;
	}
	else
	{
		result_width = a_image.width;
		x_min = width;
	}
	if (height > a_image.height) {
		result_height = height;
		y_min = a_image.height;
	}
	else
	{
		result_height = a_image.height;
		y_min = height;
	}
	Image<T> result_image(result_width, result_height);
	for (size_t i = 0; i < x_min; ++i) {
		for (size_t j = 0; j < y_min; ++j) {
			result_image.image[i][j] = image[i][j] * a_image.image[i][j];
		}
	}
	if (width > a_image.width || width < a_image.width) {
		for (size_t i = x_min; i < result_width; ++i) {
			for (size_t j = 0; j < result_height; ++j) {
				result_image.image[i][j] = image[i][j];
			}
		}
	}
	if (height > a_image.height || height < a_image.height) {
		for (size_t i = 0; i < x_min; ++i) {
			for (size_t j = y_min; j < result_height; ++j) {
				result_image.image[i][j] = image[i][j];
			}
		}
	}
	return result_image;
}

//void get_roi(const Image& a_image, size_t& x_min, size_t& y_min, size_t& result_width, size_t& result_height) {}

template <typename T>
Image<T> Image<T>::operator +(const Image& a_image) const {
	size_t x_min = 0, y_min = 0, result_width, result_height;
	if (width > a_image.width) {
		result_width = width;
		x_min = a_image.width;
	}
	else
	{
		result_width = a_image.width;
		x_min = width;
	}
	if (height > a_image.height) {
		result_height = height;
		y_min = a_image.height;
	}
	else
	{
		result_height = a_image.height;
		y_min = height;
	}
	Image<T> result_image(result_width, result_height);
	for (size_t i = 0; i < x_min; ++i) {
		for (size_t j = 0; j < y_min; ++j) {
			result_image.image[i][j] = image[i][j] + a_image.image[i][j];
		}
	}
	if (width > a_image.width || width < a_image.width) {
		for (size_t i = x_min; i < result_width; ++i) {
			for (size_t j = 0; j < result_height; ++j) {
				result_image.image[i][j] = image[i][j];
			}
		}
	}
	if (height > a_image.height || height < a_image.height) {
		for (size_t i = 0; i < x_min; ++i) {
			for (size_t j = y_min; j < result_height; ++j) {
				result_image.image[i][j] = image[i][j];
			}
		}
	}

	return result_image;
}

//void copy_outside_roi(...)

template <typename T>
Image<T> Image<T>::operator *(const T a_b) const {
	Image<T> result_image(width, height);
	for (size_t i = 0; i < width; ++i) {
		for (size_t j = 0; j < height; ++j) {
			result_image.image[i][j] = image[i][j] * a_b;
		}
	}
	return result_image;
}

template <typename T>
Image<T> Image<T>::operator +(const T a_b) const {
	Image<T> result_image(width, height);
	for (size_t i = 0; i < width; ++i) {
		for (size_t j = 0; j < height; ++j) {
			result_image.image[i][j] = image[i][j] + a_b;
		}
	}
	return result_image;
}

/*template <typename T>
binaryimage<T> binaryimage<T>::operator!() const {
	binaryimage<T> result_image(width, height);
	for (size_t i = 0; i < width; ++i) {
		for (size_t j = 0; j < height; ++j) {
			if (image[i][j] == True)
				result_image.image[i][j] = False;
			else
				result_image.image[i][j] = True;
		}
	}
	return result_image;
}*/

template <typename T>
bool Image<T>::operator ==(const Image& a_image) const {
	//if (width != a_image.width || height != a_image.height)
	//	return false;

	if (width == a_image.width && height == a_image.height) {
		for (size_t i = 0; i < width; ++i) {
			for (size_t j = 0; j < height; ++j) {
				if (image[i][j] == a_image.image[i][j])
					continue;
				else
				{
					return false;
				}
			}
		}
		return true;
	}
	else
	{
		return false;
	}
}

template <typename T>
typename vector <vector<T>>::iterator Image<T>::begin() const {
	return image[0].begin();
}

template <typename T>
typename vector<vector<T>>::iterator Image<T>::end() const {
	return image[width-1].end();
}

template <typename T>
ostream& operator <<(ostream& os, const Image<T>& a_image) {
	for (size_t i = 0; i < a_image.get_width(); ++i) {
		for (size_t j = 0; j < a_image.get_height(); ++j) {
			os << "\t" << a_image(i, j);
		}
		os << endl;
	}
	return os;
}

/*template <>
ostream& operator <<(ostream& os, const Image<char>& a_image) {
	for (size_t i = 0; i < a_image.get_width(); ++i) {
		for (size_t j = 0; j < a_image.get_height(); ++j) {
			//if (a_image(i, j))
			//	os << "\t" << a_image(i, j);
			//else
			os << "\t" << (int)a_image(i, j);
		}
		os << endl;
	}
	return os;
}*/

template <typename T>
double Image<T>::ratio() const {
	double temp = 0, d_width = width, d_height = height;
	for (size_t i = 0; i < width; ++i) {
		for (size_t j = 0; j < height; ++j) {
			if (image[i][j])
				temp++;
		}
	}
	return(temp / (d_width * d_height));
}



template <typename T>
size_t Image<T>::get_width() const {
	return width;
}

template <typename T>
size_t Image<T>::get_height() const {
	return height;
}

template <typename T>
Image<T>::~Image<T>() {}

template <typename T>
void Image<T>::print_im()const
{
	for (auto it : image)
	{
		for (auto iter : it)
			cout << "\t" << iter;
		cout << endl;
	}
}