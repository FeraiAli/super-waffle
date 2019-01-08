#include "BaseTileMap.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <GameFramework/Framework/Context.hpp>
#include <fstream>
#include <cassert>

namespace Settings
{
    static const std::string& mapFileName = "../sidescroller/TileMap/ExportFiles/TILE_MAP_TEST.txt";
    static const sf::Vector2u tileCounts = {40, 30};
}

const std::vector<BaseTileMap::TileRow> &BaseTileMap::GetTiles() const
{
    return m_tiles;
}

void BaseTileMap::importMap()
{
    std::ifstream file(Settings::mapFileName);

    std::vector<std::string> tileMapString;
    std::string line;
    while(std::getline(file, line))
    {
        tileMapString.push_back(line);
    }

    const auto windowSize = Context::Get<sf::RenderWindow>().getSize();
    m_tileSize.x = windowSize.x / Settings::tileCounts.x;
    m_tileSize.y = windowSize.y / Settings::tileCounts.y;

    m_tiles.clear();
    m_tiles.resize(Settings::tileCounts.y, TileRow(Settings::tileCounts.x));
    for(size_t row = 0; row < Settings::tileCounts.y; row++)
    {
        for(size_t col = 0; col < Settings::tileCounts.x; col++)
        {
            sf::RectangleShape box;

            box.setFillColor(AirColor);
            if(row < tileMapString.size() && col < tileMapString[row].size())
            {
                if(tileMapString[row][col] == '#') { box.setFillColor(SolidColor); }
            }

            box.setSize(m_tileSize);
            box.setOutlineColor(sf::Color::Black);
            box.setPosition(col * m_tileSize.x, row * m_tileSize.y);
            m_tiles[row][col] = std::move(box);
        }
    }
}

void BaseTileMap::exportMap()
{
    std::ofstream file(Settings::mapFileName);

    for(const auto& tileRow : m_tiles)
    {
        std::string line;
        line.reserve(tileRow.size());
        for(auto tile : tileRow)
        {
            if     (tile.getFillColor() == SolidColor) { line.push_back('#'); }
            else if(tile.getFillColor() == AirColor)   { line.push_back('0'); }
            else
            {
                assert(false and "While exporting map, found unknown TileType!");
            }
        }
        file << line << '\n';
    }
}
