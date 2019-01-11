#include "ResourcesMgr.h"
#include <iostream>

void ResourcesMgr::RegisterFont(const std::string& key, const std::string& path)
{
    m_fonts[key].loadFromFile(path);
}

void ResourcesMgr::RegisterTexture(const std::string& key, const std::string& path, const sf::IntRect& srcRect)
{
    m_textures[key].loadFromFile(path, srcRect);
}

const sf::Font *ResourcesMgr::GetFont(const std::string& key) const
{
    auto iter = m_fonts.find(key);
    if (iter != m_fonts.end())
    {
        return &iter->second;
    }

    return nullptr;
}

const sf::Texture *ResourcesMgr::GetTexture(const std::string& key) const
{
    auto iter = m_textures.find(key);
    if (iter != m_textures.end())
    {
        return &iter->second;
    }

    return nullptr;
}
