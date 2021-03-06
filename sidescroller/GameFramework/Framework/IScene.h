#pragma once
#include <SFML/Window/Event.hpp>
#include <memory>

class IScene
{
public:
    using uPtr = std::unique_ptr<IScene>;

    IScene() = default;
    virtual ~IScene() = default;

    virtual void Init(){}
    virtual void Deinit(){}

    virtual void OnMouseEvent(const sf::Event::MouseButtonEvent& mouseEvent){}

    virtual void Show(){}
    virtual void Hide(){}

    virtual void Process() = 0;
};
