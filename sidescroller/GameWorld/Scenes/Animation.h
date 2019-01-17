#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <vector>
#include <string>
#include <chrono>

class Animation
{
public:
    void Init(const std::vector<std::string>& animationFrames,
              std::chrono::milliseconds duration,
              bool repeatable = true);
    void Start();

    bool IsFinished() const;
    bool IsRepeatable() const;
    const sf::Texture* Step(std::chrono::milliseconds frameTime);

private:
    bool m_running = false;
    bool m_repeat = true;
    std::chrono::milliseconds m_elapsed = std::chrono::milliseconds::zero();
    std::chrono::milliseconds m_duration = std::chrono::milliseconds::zero();
    std::vector<const sf::Texture*> m_animationTextures;
};
