#include "SpriteBatcher.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace details
{
const uint32_t inactiveLimit = 500;

template <typename...>
struct hash;

template <typename T>
struct hash<T> : public std::hash<T>
{
    using std::hash<T>::hash;
};

template <typename T, typename... Rest>
struct hash<T, Rest...>
{
    inline std::size_t operator()(const T& v, const Rest&... rest)
    {
        std::size_t seed = hash<Rest...>{}(rest...);
        seed ^= hash<T>{}(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        return seed;
    }
};

size_t calculateHash(const sf::Sprite& sprite)
{
    static hash<uint32_t, int32_t, int32_t, int32_t, int32_t> hasher;
    return hasher(sprite.getTexture()->getNativeHandle(),
                  sprite.getTextureRect().left,
                  sprite.getTextureRect().top,
                  sprite.getTextureRect().width,
                  sprite.getTextureRect().height);
}
} // end of details

namespace sf
{

void SpriteBatcher::Add(const Sprite &sprite)
{
    if(nullptr == sprite.getTexture())
    {
        return;
    }

    const auto hash = details::calculateHash(sprite);

    auto& batch = m_batches[hash];
    batch.texture = sprite.getTexture();
    batch.Add(sprite);
}

void SpriteBatcher::draw(RenderTarget &target, RenderStates state) const
{
    for(const auto& p : m_batches)
    {
        auto& batch = p.second;
        state.texture = batch.texture;
        state.blendMode = sf::BlendAdd;
        target.draw(batch.vertices.data(), batch.count * 4, sf::Quads, state);
    }
}

void SpriteBatcher::Refresh()
{
    for(auto iter = m_batches.begin(); iter != m_batches.end(); ++iter)
    {
        auto& batch = (iter->second);
        batch.Refresh();
//        if ( batch.inactive >= details::inactiveLimit )
//        {
//            m_batches.erase(iter);
//        }
    }
}

void SpriteBatcher::Clear()
{
    m_batches.clear();
}

}
