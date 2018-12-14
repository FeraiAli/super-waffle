#include "Image.h"

bool Image::Load(const char *fileName)
{
    m_texture.loadFromFile(fileName);
    return true;
}

sf::Texture *Image::GetTexture()
{
    return &m_texture;
}

int32_t Image::GetAtlasWidth() const
{
    return m_texture.getSize().x;
}

int32_t Image::GetAtlasHeigh() const
{
    return m_texture.getSize().y;
}
