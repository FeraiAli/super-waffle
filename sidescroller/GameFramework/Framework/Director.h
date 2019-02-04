#pragma once
#include "IScene.h"
#include <unordered_map>
#include <stack>

class Director
{
public:
    void Register(const std::string& name, IScene::uPtr&& scene);
    void StartWith(const std::string& name);

    void Change(const std::string& name);
    void Push(const std::string& name);
    void Pop();

    void InitScenes();
    void DeinitScenes();
    void OnMouseEvent(const sf::Event::MouseButtonEvent& mouseEvent);
    void Process();
private:
    using SceneHolder = std::unordered_map<std::string, IScene::uPtr>;

    SceneHolder m_scenes;
    SceneHolder::iterator m_currentScene = m_scenes.end();

    std::stack<std::string> m_stackedScenes;
};
