#ifndef IMAGELOADER_H
#define IMAGELOADER_H

#include <iostream>

class ImageLoader
{
public:
	//unsigned char*  ImageLoader::loadFromFile(const char* file)
	static unsigned char* loadFromFile(const char* file, int* width, int* height);

	static unsigned char* loadFromMemory(int length, int* width, int* height);

	static void freeImage(unsigned char* image);
};

#endif