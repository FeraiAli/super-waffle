#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <timelinefx_parser/TLFXAnimImage.h>

class Image : public TLFX::AnimImage
{
public:
    bool Load(const char* fileName) final override;
    sf::Texture* GetTexture();

    int32_t GetAtlasWidth() const;
    int32_t GetAtlasHeigh() const;
private:
    sf::Texture m_texture;
};
