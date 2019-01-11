#include "DrawSystem.h"
#include <GameFramework/Framework/Context.hpp>
#include <GameFramework/Entita/Pool.h>

#include <SFML/Graphics/RenderWindow.hpp>
#include "../Components/Components.h"

void DrawSystem::Process()
{
    auto& window = Context::Get<sf::RenderWindow>();
    auto& pool = Context::Get<Entita::Pool>();

    for(auto entity : pool.GetEntities<Body, Skin>())
    {
        auto& body = entity->GetComponent<Body>();
        auto& skin = entity->GetComponent<Skin>();
        skin.setPosition(body.getPosition());
        window.draw(skin);
    };

    for(auto entity : pool.GetEntities<Body, Drawable>())
    {
        auto& body = entity->GetComponent<Body>();
        auto& drawble = entity->GetComponent<Drawable>();
        drawble.setPosition(body.getPosition());
        window.draw(drawble);
    };
}
