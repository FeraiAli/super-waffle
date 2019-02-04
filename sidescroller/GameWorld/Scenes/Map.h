#pragma once
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Map
{
public:
    struct Tile : public sf::RectangleShape
    {
        bool isBox = false;
    };

    void Init();
    void SaveMap();
    void Process(sf::RenderWindow& window);
    std::vector<std::vector<Tile>>& GetMapTiles();

private:
    void readMap();
    void editTile(bool used);
private:
    bool editorMode = false;

    sf::Sprite box;
    sf::Vector2i m_mousePos;
    std::vector<std::vector<Map::Tile>> m_mapTiles;
};
