#pragma once
#include <GameFramework/Framework/IScene.h>
#include <SFML/Graphics/RectangleShape.hpp>

#include <vector>

class BaseTileMap : public IScene
{
public:
    using TileRow = std::vector<sf::RectangleShape>;

    const std::vector<TileRow>& GetTiles() const;
protected:
    void refreshTiles();
    void importMap();
    void exportMap();


    std::vector<TileRow> m_tiles;

    const sf::Color SolidColor = sf::Color(11, 102, 35);
    const sf::Color AirColor = sf::Color(200, 224, 250);
    sf::Vector2f m_tileSize;
};

