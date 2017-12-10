#ifndef __IMAGELOADER__
#define __IMAGELOADER__

#include <iostream>

#include "Texture.hpp"

class ImageLoader
{
public:
	static Texture* loadFromFile(const char* file);

	static Texture* loadFromMemory(void* buffer, int length);

	static void freeImage(unsigned char* image);
};

#endif