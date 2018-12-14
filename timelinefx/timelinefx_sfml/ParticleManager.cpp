#include "ParticleManager.h"
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>

#include "Image.h"

#include <array>
#include <iostream>
#include <cmath>

ParticleManager::ParticleManager()
    : TLFX::ParticleManager(5000, 5)
{
}

void ParticleManager::SetRenderWindow(sf::RenderWindow *window)
{
    m_windowPtr = window;
}

void ParticleManager::DrawSprite(TLFX::AnimImage* animImage, float posX, float posY,
                                 float frame, float originX, float originY,
                                 float rotation, float scaleX, float scaleY,
                                 uint8_t r, uint8_t g, uint8_t b, float a,
                                 bool additive)
{
    uint8_t alpha = static_cast<uint8_t>(a * 255);
    if(nullptr == animImage || alpha == 0 || scaleX == 0.0f || scaleY == 0.0f)
    {
        return;
    }

    auto image = static_cast<Image*>(animImage);
    const int frameI32 = static_cast<int32_t>(frame);

    sf::IntRect textureRect;
    textureRect.width = static_cast<int>(animImage->GetWidth());
    textureRect.height = static_cast<int>(animImage->GetHeight());

    textureRect.left = frameI32 % (image->GetAtlasWidth() / static_cast<int32_t>(image->GetWidth()));
    textureRect.left *= textureRect.width;

    textureRect.top = frameI32 / (image->GetAtlasHeigh() / static_cast<int32_t>(image->GetHeight()));
    textureRect.top *= textureRect.height;

    sf::Sprite sprite;
    sprite.setTexture(*image->GetTexture());
    sprite.setTextureRect(textureRect);
    sprite.setPosition(sf::Vector2f(posX, posY));
    sprite.setOrigin(sf::Vector2f(originX, originY));
    sprite.setScale(sf::Vector2f(scaleX, scaleY));
    sprite.setRotation(rotation);
    sprite.setColor({r,g,b,alpha});

    m_batcher.add(sprite);
}

void ParticleManager::Flush()
{
    m_windowPtr->draw(m_batcher);
    m_batcher.refresh();
}


