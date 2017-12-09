#include "ImageLoader.h"

//#include ...
//#include ...
//#include ...
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture* ImageLoader::loadFromFile(const char* file)
{
	Texture* texture = new Texture();
	int comp = 0, req_comp = 0;

	// load the texture image from image file
	unsigned char* image = stbi_load(file, &texture->width, &texture->height, &comp, STBI_rgb_alpha);

	// do additional data processing here

	if (image == nullptr)
		std::cout << "Stb_image failed to load texture from file: " << file << std::endl;
	else
		std::cout << "Stb_image successfully loaded texture from file: " << file << " | width: " << texture->width << " | height: " << texture->height << " | composition: " << comp << std::endl;

	// store the image inside the texture class as an unsigned char*
	texture->image = image;

	return texture;
}

Texture* ImageLoader::loadFromMemory(void* buffer, int length)
{
	Texture* texture = new Texture();
	const stbi_uc* temp;

	// convert the void pointer into stbi_uc
	temp = static_cast<stbi_uc*>(buffer); // not tested yet (wip)

	// load the texture image from memory
	unsigned char* image = stbi_load_from_memory(temp, length, &texture->width, &texture->height, 0, STBI_rgb_alpha);

	// do additional data processing here

	if (image == nullptr)
		std::cout << "Stb_image failed to load texture from memory" << std::endl;
	else
		std::cout << "Stb_image successfully loaded texture from memory | width: " << texture->width << " | height: " << texture->height << std::endl;

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