#pragma once
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <GameFramework/Framework/IScene.h>

class GameEditorScene : public IScene
{
public:
    void Deinit() final override;
    void Show() final override;
    void Hide() final override;
    void Process() final override;

    static std::vector<std::string> GetStringMap();
    static sf::Vector2u GetTilesCount();

    static const sf::Color SolidColor;
    static const sf::Color AirColor;
private:
    void loadMap();
    void saveMap();

    using RowTile = std::vector<sf::RectangleShape>;
    std::vector<RowTile> m_tiles;

    sf::RectangleShape m_selectedTile;
    sf::Vector2f m_tileSize;
};

