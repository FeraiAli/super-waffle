#pragma once
#include "Batch.h"
#include <unordered_map>

namespace sf
{

class SpriteBatcher : public Drawable
{
public:
    void Add(const sf::Sprite& sprite);
    void Refresh();
    void Clear();
private:
    void draw(RenderTarget& target, RenderStates state) const final override;
private:
    std::unordered_map<size_t, Batch> m_batches;
};

}
