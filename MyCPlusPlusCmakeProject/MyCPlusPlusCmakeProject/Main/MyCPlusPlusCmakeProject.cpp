// MyCPlusPlusCmakeProject.cpp : Defines the entry point for the application.
//

#include "CMakeLibrary.h"
#include "QRGenerator/QrCodeManager.h"

#include <iostream>

using namespace std;

int main()
{
	cout << "Hello CMake." << endl;

	CMakeLibrary::instance();

	QrCodeManager::instance().generateQRImage("Hello World!", 10);

	return 0;
}
