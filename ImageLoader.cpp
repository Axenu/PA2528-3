#include "ImageLoader.h"

//#include ...
//#include ...
//#include ...
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

unsigned char* ImageLoader::loadFromFile(const char* file, int width, int height)
{
	int comp = 0, req_comp = 0;
	unsigned char* image = stbi_load(file, &width, &height, &comp, STBI_rgb_alpha);

	// do additional data processing here

	if (image == nullptr)
		std::cout << "Stb_image failed to load texture from file: " << file << std::endl;
	else
		std::cout << "Stb_image successfully loaded texture from file: " << file << " | width: " << width << " | height: " << height << " | composition: " << comp << std::endl;


	return image;
}

unsigned char* ImageLoader::loadFromMemory(void* buffer, int length, int width, int height)
{
	const stbi_uc* temp;

	temp = static_cast<stbi_uc*>(buffer); // not tested yet (wip)

	unsigned char* image = stbi_load_from_memory(temp, length, &width, &height, 0, STBI_rgb_alpha);

	if (image == nullptr)
		std::cout << "Stb_image failed to load texture from memory" << std::endl;
	else
		std::cout << "Stb_image successfully loaded texture from memory | width: " << width << " | height: " << height << std::endl;

	return image;
}

void ImageLoader::freeImage(unsigned char* image)
{
	if (image)
		stbi_image_free(image);
}