#include "ImageLoader.h"

//#include ...
//#include ...
//#include ...
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture* ImageLoader::loadFromFile(const char* file)
{
	Texture* texture = new Texture();

	// load the texture image from image file
	unsigned char* image = stbi_load(file, &texture->width, &texture->height, &texture->composition, STBI_rgb_alpha);

	// do additional data processing here

	// debugging code
	if (image == nullptr)
		std::cout << "Stb_image failed to load texture " << file << std::endl;
	else
	{
		std::cout << "Stb_image successfully loaded texture from " << file << std::endl;
		std::cout << "Width_______| " << texture->width << std::endl;
		std::cout << "Height______| " << texture->height << std::endl;
		std::cout << "Composition_| " << texture->composition << std::endl;
	}		

	// store the image inside the texture class as an unsigned char*
	texture->image = image;

	return texture;
}

Texture* ImageLoader::loadFromMemory(void* buffer, int length)
{
	Texture* texture = new Texture();
	const stbi_uc* temp; // temp pointer used for converting the void* pointer to a format that stbi can read.

	// convert the void pointer into stbi_uc
	temp = static_cast<stbi_uc*>(buffer); // not tested yet (wip)

	// load the texture image from memory
	unsigned char* image = stbi_load_from_memory(temp, length, &texture->width, &texture->height, &texture->composition, STBI_rgb_alpha);

	// do additional data processing here

	if (image == nullptr)
		std::cout << "Stb_image failed to load texture from memory." << std::endl;
	else
	{
		std::cout << "Stb_image successfully loaded texture from memory." << std::endl;
		std::cout << "Width_______| " << texture->width << std::endl;
		std::cout << "Height______| " << texture->height << std::endl;
		std::cout << "Composition_| " << texture->composition << std::endl;
	}

	// store the image inside the texture class as an unsigned char*
	texture->image = image;

	return texture;
}

void ImageLoader::freeImage(unsigned char* image)
{
	if (image)
	{
		stbi_image_free(image);
	}
}