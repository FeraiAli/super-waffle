#include "Director.h"
#include <assert.h>

void Director::Register(const std::string &name, IScene::uPtr &&scene)
{
    m_scenes[name] = std::move(scene);
}

void Director::StartWith(const std::string &name)
{
    auto iter = m_scenes.find(name);
    assert(iter != m_scenes.end() and "Start with scene that hasn't been registered!");

    m_currentScene = iter;
    m_currentScene->second->Show();
}

void Director::Change(const std::string &name)
{
    auto iter = m_scenes.find(name);
    assert(iter != m_scenes.end() and "Change scene that hasn't been registered!");

    m_currentScene->second->Hide();
    m_currentScene = iter;
    m_currentScene->second->Show();
}

void Director::Push(const std::string &name)
{
    auto iter = m_scenes.find(name);
    assert(iter != m_scenes.end() and "Push scene that hasn't been registered!");

    m_stackedScenes.push(iter->first);
    Change(name);
}

void Director::Pop()
{
    assert(false == m_stackedScenes.empty() and "Can't Pop scene, the stack is empty!");

    const std::string prevSceneName = m_stackedScenes.top();
    m_stackedScenes.pop();
    Change(prevSceneName);
}

void Director::InitScenes()
{
    for(auto& p : m_scenes)
    {
        p.second->Init();
    }
}

void Director::Process()
{
    m_currentScene->second->Process();
}
