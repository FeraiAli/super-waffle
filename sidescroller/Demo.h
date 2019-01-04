#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <Actions/Actor.h>
#include <chrono>
#include <memory>

class Demo
{
public:
    Demo();
    void Update(std::chrono::milliseconds dt);
    void Draw(sf::RenderWindow& window);
private:
    std::vector<sf::Texture> spadeTextures;
    std::vector<std::shared_ptr<sf::Sprite>> spadeSprites;
    Action::ActionManager m_actionManager;
};
