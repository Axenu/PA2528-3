#ifndef __IMAGELOADER__
#define __IMAGELOADER__

//#include ...
//#include ...
//#include ...
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

class ImageLoader
{
public:
	//unsigned char*  ImageLoader::loadFromFile(const char* file)
	static unsigned char* loadFromFile(const char* file, int* width, int* height)
	{
		unsigned char* image = stbi_load(file, width, height, 0, 0);

		// process data

		return image;
	}

	static unsigned char* loadFromMemory(int length, int* width, int* height)
	{
		const stbi_uc* buffer;

		unsigned char* image = stbi_load_from_memory(buffer, length, width, height, 0, 0);

		return image;
	}

	static void freeImage(unsigned char* image)
	{
		if (image)
			stbi_image_free(image);
	}
};

#endif