#pragma once
#include "SFML/Graphics/Sprite.hpp"
#include <map>
#include <vector>
#include <string>
#include <chrono>

class Drawable : public sf::Sprite
{
public:
    struct Animation
    {
        bool isRepeated = false;
        std::vector<std::string> frames;
        std::chrono::milliseconds elapsed = std::chrono::milliseconds::zero();
        std::chrono::milliseconds duration = std::chrono::milliseconds::zero();
    };

    void AddAnimations(std::string characterAnimation ,
                       std::vector<std::string> framesContainer,
                       std::chrono::milliseconds animationDuration);

	bool HasAnimation() const;
    bool SetAnimation(std::string characterAnimation);
    std::map<std::string, Animation>::iterator GetCurrentAnimation();

private:
    std::map<std::string, Animation> m_animations;
    std::map<std::string, Animation>::iterator m_currentAnim = m_animations.end();

};


