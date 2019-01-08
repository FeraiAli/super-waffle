#include "TileEditor.h"
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <GameFramework/Framework/Context.hpp>
#include <fstream>

void TileEditor::Show()
{
    BaseTileMap::importMap();

    m_selectedTile.setSize(BaseTileMap::m_tileSize * 0.9f);
    m_selectedTile.setOutlineColor(sf::Color::Black);
    m_selectedTile.setOutlineThickness(1.0f);
    m_selectedTile.setOrigin(m_selectedTile.getSize().x / 2, m_selectedTile.getSize().y / 2);
    m_selectedTile.setFillColor(SolidColor);

    for(auto& tileRow : m_tiles)
    {
        for(auto& tile : tileRow)
        {
            tile.setOutlineThickness(1.0f);
        }
    }
}

void TileEditor::Hide()
{
    BaseTileMap::exportMap();
}

void TileEditor::Process()
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
