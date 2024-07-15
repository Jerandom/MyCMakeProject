// MyCPlusPlusCmakeProject.cpp : Defines the entry point for the application.
//

#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <iostream>
#include <regex>
#include <algorithm>
#include <cassert>

#include "QRGenerator/QrCodeManager.h"

using namespace std;

int main()
{
    QrCodeManager::instance().generateHighResQRCode("asdas", 1, 1);
 
    return 0;
}
