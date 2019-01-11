#include "GameEditorScene.h"
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <GameFramework/Framework/Context.hpp>
#include <GameWorld/EntityFactory/EntityFactory.h>
#include <fstream>
#include <cmath>

namespace Settings
{
    static const std::string& mapFileName = "../sidescroller/Config/PROTOTYPE_MAP.txt";
}

const sf::Color GameEditorScene::SolidColor(11, 102, 35);
const sf::Color GameEditorScene::AirColor(200, 224, 250);

void GameEditorScene::Deinit()
{
    //saveMap();
}

void GameEditorScene::Show()
{
    loadMap();

    m_selectedTile.setSize(EntitySettings::Size * 0.9f);
    m_selectedTile.setOutlineColor(sf::Color::Black);
    m_selectedTile.setOutlineThickness(1.0f);
    m_selectedTile.setOrigin(m_selectedTile.getSize().x / 2, m_selectedTile.getSize().y / 2);
    m_selectedTile.setFillColor(SolidColor);
}

void GameEditorScene::Hide()
{
    saveMap();
}

void GameEditorScene::Process()
{
    if( sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) )
    {
        m_selectedTile.setFillColor(AirColor);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
    {
        m_selectedTile.setFillColor(SolidColor);
    }

    auto& window = Context::Get<sf::RenderWindow>();

    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        auto mousePos = static_cast<sf::Vector2i>(sf::Mouse::getPosition(window));
        for(auto& rowTile : m_tiles)
        {
            for(auto& tile : rowTile)
            {
                if(tile.getGlobalBounds().contains(window.mapPixelToCoords(mousePos)))
                {
                    tile.setFillColor(m_selectedTile.getFillColor());
                }
            }
        }
    }

    for(const auto& tileRow : m_tiles)
    {
        for(const auto& tile : tileRow)
        {
            window.draw(tile);
        }
    }

    auto mousePos = static_cast<sf::Vector2i>(sf::Mouse::getPosition(window));
    m_selectedTile.setPosition(window.mapPixelToCoords(mousePos));
    window.draw(m_selectedTile);
}

std::vector<std::string> GameEditorScene::GetStringMap()
{
    std::ifstream file(Settings::mapFileName);

    std::vector<std::string> tileMapString;
    std::string line;
    while(std::getline(file, line))
    {
        tileMapString.push_back(line);
    }
    return tileMapString;
}


void GameEditorScene::loadMap()
{
    auto tileMapString = GetStringMap();
    const auto windowSize = Context::Get<sf::RenderWindow>().getSize();
    sf::Vector2u tilesCount;
    tilesCount.x = static_cast<uint32_t>(std::floor(windowSize.x / EntitySettings::Size.x));
    tilesCount.y = static_cast<uint32_t>(std::floor(windowSize.y / EntitySettings::Size.y));

    m_tiles.clear();
    m_tiles.resize(tilesCount.y, RowTile(tilesCount.x));
    for(size_t row = 0; row < tilesCount.y; row++)
    {
        for(size_t col = 0; col < tilesCount.x; col++)
        {
            sf::RectangleShape box;

            box.setFillColor(AirColor);
            if(row < tileMapString.size() && col < tileMapString[row].size())
            {
                if(tileMapString[row][col] == '#') { box.setFillColor(SolidColor); }
            }

            box.setSize(EntitySettings::Size);
            box.setOutlineColor(sf::Color::Black);
            box.setOutlineThickness(1.0f);
            box.setPosition(col * EntitySettings::Size.x, row * EntitySettings::Size.y);
            box.setSize(EntitySettings::Size);
            m_tiles[row][col] = std::move(box);
        }
    }
}

void GameEditorScene::saveMap()
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


