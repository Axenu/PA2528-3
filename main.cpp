#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <chrono>

#include "ImporterManager.h"
#include "ImporterTester.h"


#include "PackageReader.hpp"


int main()
{
	ImporterTester::imageFileTest("test_files/map_01.png");

	PackageReader::setPackage("..\\..\\PA2528-3\\package tool\\res");

    return 0;
}
