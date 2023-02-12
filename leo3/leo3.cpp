#include <iostream>
#include "Image.h"

int main()
{

	Image<int> bimage(3, 3);
	bimage(0, 0) = true;
	bimage(1, 1) = false;
	cout << "bimage:\n" << bimage << endl;

	Image<int> bimage1(3, 3);
	bimage1(0, 0) = true;
	bimage1(1, 1) = true;
	cout << "bimage1:\n" << bimage1 << endl;

	cout << bimage + bimage1 << endl;
	cout << bimage * bimage1 << endl;

	Image<int> bimage2(3, 3);
	bimage2(0, 0) = 3;
	bimage2(1, 1) = 7;
	cout << "bimage2:\n" << bimage2 << endl;

	Image<int> bimage3(3, 3);
	bimage3(0, 0) = 4;
	bimage3(1, 1) = 1;
	cout << "bimage3:\n" << bimage3 << endl;

	cout << bimage2 + bimage3 << endl;
	cout << bimage2 * bimage3 << endl;

	Image<short> bimage4(3, 3);
	bimage4(0, 0) = 5;
	bimage4(1, 1) = 7;
	cout << "bimage4:\n" << bimage4 << endl;

	Image<char> bimage5(3, 3);
	bimage5(0, 0) = 's';
	bimage5(1, 1) = 'a';
	cout << "bimage5:\n" << bimage5 << endl;

	Image<char> bimage6(3, 3);
	bimage6(0, 0) = 'd';
	bimage6(1, 1) = 'r';
	cout << "bimage6:\n" << bimage6 << endl;

	Image<float> bimage7(3, 3);
	bimage7(0, 0) = 7.1;
	bimage7(1, 1) = 7.2;
	cout << "bimage7:\n" << bimage7 << endl;

	Image<float> bimage8(3, 3);
	bimage8(0, 0) = 5.4;
	bimage8(1, 1) = 8.9;
	cout << "bimage8:\n" << bimage8 << endl;

	cout << bimage7 + bimage8 << endl;
	cout << bimage7 * bimage8 << endl;

	cout << (bimage == bimage1) << endl;

	cout << bimage2.ratio() << endl;
    return 0;
}