#pragma once
#include "../BaseTileMap.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <vector>

class TileEditor : public BaseTileMap
{
public:
    void Show() override;
    void Hide() override;

    void Process() final override;
private:
    sf::RectangleShape m_selectedTile;
};
