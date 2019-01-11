#pragma once
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <unordered_map>

class ResourcesMgr
{
public:
    void RegisterFont(const std::string& key, const std::string& path);
    void RegisterTexture(const std::string& key, const std::string& path, const sf::IntRect& srcRect = {});

    const sf::Font* GetFont(const std::string& key) const;
    const sf::Texture* GetTexture(const std::string& key) const;
private:
    std::unordered_map<std::string, sf::Font> m_fonts;
    std::unordered_map<std::string, sf::Texture> m_textures;
};
