#include "Map.h"
#include <GameFramework/Framework/Context.hpp>
#include <GameFramework/Framework/ResourcesMgr.h>
#include <SFML/Window/Event.hpp>
#include <string>
#include <fstream>
#include <iostream>

namespace
{
   static const std::string& mapPath = "../sidescroller/MapTemplate/tileMap.txt";

   static const int tileWidth = 40;
   static const int tileHeight = 30;
   static const int windowWidth = 1600;
   static const int windowHeight = 900;
}

void Map::Init()
{
    m_mapTiles.resize(windowHeight / tileHeight,
                        std::vector<Map::Tile>(windowWidth / tileWidth));

    for (size_t y = 0; y < windowHeight / tileHeight; y++)
    {
        for (size_t x = 0; x < windowWidth / tileWidth; x++)
        {
            Map::Tile tile;
            tile.setSize({tileWidth, tileHeight});
            tile.setOutlineThickness(1.0f);
            tile.setFillColor(sf::Color(0,0,0,0));
            tile.setOutlineColor(sf::Color::Black);
            tile.setPosition(tileWidth * x, tileHeight * y);
            tile.isBox = false;
            m_mapTiles[y][x] = tile;
        }
    }
    box.setTexture(*(Context::Get<ResourcesMgr>().GetTexture("box")));
    box.setScale(tileWidth / box.getGlobalBounds().width,
                 tileHeight / box.getGlobalBounds().height);

    readMap();
}

void Map::Process(sf::RenderWindow &window)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::F2))        { editorMode = true; }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::F1))   { editorMode = false; }

    if(editorMode)
    {
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))  { editTile(true);  }
        if(sf::Mouse::isButtonPressed(sf::Mouse::Right)) { editTile(false); }
    }

    m_mousePos = sf::Mouse::getPosition(window);
    for (const auto& tileRow : m_mapTiles)
    {
        for (const auto& tile : tileRow)
        {
            if(editorMode)
            {
                window.draw(tile);
            }

            if(tile.isBox)
            {
                box.setPosition(tile.getPosition());
                window.draw(box);
            }
        }
    }
}

void Map::editTile(bool used)
{
    for (size_t y = 0; y < m_mapTiles.size(); ++y)
    {
        for (size_t x = 0; x < m_mapTiles[y].size(); x++)
        {
            auto& tile = m_mapTiles[y][x];

            if (tile.getGlobalBounds().contains(m_mousePos.x, m_mousePos.y))
            {
                auto& tile = m_mapTiles[y][x];
                tile.isBox = used;
                break;
            }
        }
    }
}

void Map::readMap()
{
    std::string line;
    std::ifstream mapFile(mapPath);
    std::vector<std::string> m_map;

    if (mapFile.is_open())
    {
        while (getline(mapFile, line) )
        {
            m_map.push_back(line);
        }
    }

    for (size_t y = 0; y < m_map.size(); ++y)
    {
        auto& str = m_map[y];
        size_t widthPos = 0;
        for (auto iter = str.begin(); iter != str.end(); iter++)
        {
            if (*iter == '#')
            {
                auto& tile = m_mapTiles[y][widthPos];
                tile.isBox = true;
            }
            widthPos++;
        }
    }
}

void Map::SaveMap()
{
    std::ofstream file;
    file.open(mapPath);

    for (auto& tiles : m_mapTiles)
    {
        for (auto& tile : tiles)
        {
            if (false == tile.isBox)
            {
                file << '0';
            }
            else
            {
                file << '#';
            }
        }
        file << '\n';
    }
    file.close();
}



