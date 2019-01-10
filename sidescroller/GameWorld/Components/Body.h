#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>

class b2Body;
struct Body
{
    enum class Type { Dynamic, Static };
    explicit Body(sf::Vector2f sz, Type type = Type::Static);
    ~Body();

    void setPosition(sf::Vector2f pos);
    void setPosition(float x, float y);

    sf::Vector2f getPosition() const;
    void updatePositions();

public:
    bool isGrounded = false;
    sf::Vector2f velocity;
    sf::Vector2f size;

private:
    b2Body* body = nullptr;
};
