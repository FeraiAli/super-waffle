#include "Demo.h"
#include <CustomActions/SpriteActions.h>
#include <SFML/Window/Event.hpp>

using namespace std::chrono_literals;

Demo::Demo()
{
    spadeTextures.reserve(13*4);
    auto createCard = [this](std::string name, float yPos)
    {
        for(int i = 1; i <= 13; i++)
        {
            spadeTextures.push_back(sf::Texture());

            std::string cardName = "card_" + std::to_string(i) + name;
            auto& texture = spadeTextures.back();
            texture.loadFromFile("../sidescroller/Assets/" + cardName);

            auto sprite = std::make_shared<sf::Sprite>();
            sprite->setTexture(texture);

            sprite->setPosition(250 + (i * (sprite->getLocalBounds().width)), yPos);
            sprite->setOrigin(sprite->getLocalBounds().width/2, sprite->getLocalBounds().height/2);
            spadeSprites.push_back(std::move(sprite));
        }
    };

    createCard("_clover.png", 100);
    createCard("_diamond.png", 200);
    createCard("_heart.png", 300);
    createCard("_spade.png", 400);

    //Actor::Run( Action::MoveTo(spadeSprites[1], {0.0f, 500.0f}, 2s, Tween::inSine) );
    //Actor::Run( Action::MoveTo(spadeSprites[2], {0.0f, 500.0f}, 2s, Tween::outSine) );

    auto runAction = [this](int id)
    {
        auto justSprite = spadeSprites[id];
        Actor::Run( Action::Sequence
                    ({
                         Action::MoveTo(justSprite, {300 + (id+1) * 10.0f, 500.0f}, 500ms),
                         Action::MoveBy(justSprite, {100.0f, -300.0f}, 500ms),
                         Action::ScaleTo(justSprite, {1.0f, 2.0f}, 250ms),
                         Action::ScaleTo(justSprite, {0.5f, 2.0f}, 250ms),
                         Action::ScaleTo(justSprite, {1.0f, 1.0f}, 250ms),
                         Action::MoveTo(justSprite, {500 + (id+1) * 10.0f, 500.0f}, 250ms),
                         Action::RotateBy(justSprite, 3000.0f, 1s),
                         Action::Repeat
                         (
                             Action::Parallel
                             ({
                                 Action::ScaleBy(justSprite, {1.0f, 1.0f}, 1s),
                                 Action::RotateBy(justSprite, -1200.0f, 1s),
//                                 Action::Sequence
//                                 ({
//                                     Action::MoveBy(justSprite, {0.0f, 100.0f}, 250ms),
//                                     Action::MoveBy(justSprite, {-100.0f, 0.0f}, 250ms),
//                                     Action::MoveBy(justSprite, {0.0f, -100.0f}, 250ms),
//                                     Action::MoveBy(justSprite, {-100.0f, 0.0f}, 250ms),
//                                 }),
                                 Action::Delay(2s)
                             }),
                         1),
                         Action::Parallel
                         ({
                             Action::ScaleTo(justSprite, {1.0f, 1.0f}, 500ms),
                             Action::RotateTo(justSprite, 0.0f, 500ms),
                         }),

                         Action::MoveTo(justSprite, {250 + id * justSprite->getLocalBounds().width/4, 100.0f}, 2s, Tween::outBounce)
                    }));
    };

    for(int i = 0; i < spadeSprites.size(); i++)
    {
        //runAction(i);
    }

    auto sequence = Action::Sequence({
                        Action::MoveTo(spadeSprites[0], {700.0f, 700.0f}, 2500ms, Tween::outSine),
                        Action::Delay(1000ms),
                        Action::Parallel({
                            Action::MoveTo(spadeSprites[0], {100.0f, 100.0f}, 2500ms, Tween::outSine),
                            Action::ScaleBy(spadeSprites[0], {2.0f, 2.0f}, 2500ms)
                                         })
                     });

    Actor::Run( sequence );
//    Actor::Run( Action::MoveTo(spadeSprites[12], {700.0f, 700.0f}, 2500ms) );
}

void Demo::Update(std::chrono::milliseconds dt)
{

}

void Demo::Draw(sf::RenderWindow &window)
{
    auto pos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
    for(auto sprite : spadeSprites)
    {
        if( sprite->getGlobalBounds().contains(pos))
        {
            Actor::Run( Action::ScaleTo(sprite, {1.5f, 1.5f}, 100ms) );
        }
        else
        {
            Actor::Run( Action::ScaleTo(sprite, {1.0f, 1.0f}, 200ms) );
        }
    }
    for(auto& sprite : spadeSprites) window.draw(*sprite);
//        window.draw(*spadeSprites[0]);
//        window.draw(*spadeSprites[12]);
}

