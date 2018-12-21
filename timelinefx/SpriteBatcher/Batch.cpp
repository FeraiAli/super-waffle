#include "Batch.h"
#include <SFML/Graphics/Texture.hpp>

namespace sf
{

void Batch::Refresh()
{
    if(count > 0)
    {
        count = 0;
        inactive = 0;
    }
    else
    {
        inactive++;
    }
}

void Batch::Add(const Sprite &sprite)
{
    size_t vertex_m_count = count * 4;
    if(vertex_m_count + 4 > vertices.size())
    {
        vertices.resize(vertices.size() + 4);
    }

    sf::Vector2f position(sprite.getTextureRect().left, sprite.getTextureRect().top);
    sf::Vector2f size(sprite.getTextureRect().width, sprite.getTextureRect().height);

    sf::Transform transform = sprite.getTransform();

    vertices[vertex_m_count].position = transform.transformPoint(0.0f, 0.0f);
    vertices[vertex_m_count].texCoords = position;
    vertices[vertex_m_count].color = sprite.getColor();

    vertices[vertex_m_count + 1].position = transform.transformPoint(0.0f, size.y);
    vertices[vertex_m_count + 1].texCoords = sf::Vector2f(position.x, size.y + position.y);
    vertices[vertex_m_count + 1].color = sprite.getColor();

    vertices[vertex_m_count + 2].position = transform.transformPoint(size);
    vertices[vertex_m_count + 2].texCoords = size + position;
    vertices[vertex_m_count + 2].color = sprite.getColor();

    vertices[vertex_m_count + 3].position = transform.transformPoint(size.x, 0.0f);
    vertices[vertex_m_count + 3].texCoords = sf::Vector2f(size.x + position.x, position.y);
    vertices[vertex_m_count + 3].color = sprite.getColor();

    count++;
}

}
