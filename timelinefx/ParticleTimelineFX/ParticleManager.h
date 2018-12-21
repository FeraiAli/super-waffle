#pragma once
#include <DataParser/TLFXParticleManager.h>
#include "../SpriteBatcher/SpriteBatcher.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>

#include <map>
#include <vector>

class ParticleManager : public TLFX::ParticleManager
{
public:
    ParticleManager();
    void SetRenderWindow(sf::RenderWindow* window);

    void DrawSprite(TLFX::AnimImage* animImage,
                    float posX, float posY,
                    float frame, float originX, float originY, float rotation,
                    float scaleX, float scaleY, uint8_t r, uint8_t g, uint8_t b, float a,
                    bool additive) final override;

    void Flush();
private:
    sf::SpriteBatcher m_batcher;
    sf::RenderWindow* m_windowPtr = nullptr;
};
