#pragma once
#include "GameFramework/Entita/Entity.h"
#include "SFML/System/Vector2.hpp"

struct EntitySettings
{
    static const sf::Vector2f Size;
    static const sf::Vector2f PlayerSize;
};

class EntityFactory
{
public:
    static Entita::Entity::Ptr CreateTile(sf::Vector2f pos);
	static Entita::Entity::Ptr CreatePlayer1(sf::Vector2f pos);
	static Entita::Entity::Ptr CreatePlayer2(sf::Vector2f pos);

	static Entita::Entity::Ptr CreateEnemy(sf::Vector2f pos);

};
