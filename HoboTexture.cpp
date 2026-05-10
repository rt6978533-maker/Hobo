#include <Hobo/Hobo.h>
//----------------------------------------------------------------------------------
//									Texture2D
//----------------------------------------------------------------------------------
Hobo::Texture2D::Texture2D(const char* pathFile) {
	Data = nullptr;
	Width = 0;
	Height = 0;
	FileManager::LoadTexture(*this, pathFile);
}
Hobo::Texture2D::~Texture2D() {
	FileManager::FreeTexture(*this);
}
bool Hobo::Texture2D::empty() {
	return Data == NULL || Width == 0 || Height == 0;
}

//----------------------------------------------------------------------------------
//						FileManager: LoadTexture
//----------------------------------------------------------------------------------

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

void Hobo::FileManager::STBI_FLIP_TEXTURE(bool value) {
	stbi_set_flip_vertically_on_load(value);
}
void Hobo::FileManager::LoadTexture(Texture2D& texture, std::string pathFile) {
	texture.Data = stbi_load(pathFile.c_str(), &texture.Width, &texture.Height, NULL, 4);
}
void Hobo::FileManager::FreeTexture(Texture2D& texture) {
	stbi_image_free(texture.Data);
}