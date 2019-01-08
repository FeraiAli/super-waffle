#include "AgentDrawer.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <GameFramework/Framework/Context.hpp>


size_t AgentDrawer::Requires()
{
    return static_cast<size_t>(AgentTag::Drawable);
}

void AgentDrawer::Process(std::vector<Agent::Ptr> agents)
{
    auto& window = Context::Get<sf::RenderWindow>();
    for(auto& agent : agents)
    {
        if(agent->isGrounded)
        {
            agent->shape.setFillColor(sf::Color::Red);
        }
        else
        {
            agent->shape.setFillColor(sf::Color::Green);
        }
        window.draw(agent->shape);
    }
}
