#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <memory>
#include <vector>

namespace sf
{

struct Batch
{
    using uPtr = std::unique_ptr<Batch>;
    void Refresh();
    void Add(const sf::Sprite& sprite);

    std::vector<sf::Vertex> vertices;
    uint32_t count = 0;
    uint32_t inactive = 0;

    const sf::Texture* texture = nullptr;
};
}

