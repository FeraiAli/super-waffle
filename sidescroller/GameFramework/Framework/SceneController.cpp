#include "SceneController.h"
#include <assert.h>

void SceneController::Register(const std::string &name, IScene::uPtr &&scene)
{
    m_scenes[name] = std::move(scene);
}

void SceneController::StartWith(const std::string &name)
{
    auto iter = m_scenes.find(name);
    assert(iter != m_scenes.end() and "Start with scene that hasn't been registered!");

    m_currentScene = iter;
}

void SceneController::Change(const std::string &name)
{
    auto iter = m_scenes.find(name);
    assert(iter != m_scenes.end() and "Change scene that hasn't been registered!");

    m_currentScene->second->Hide();
    m_currentScene = iter;
    m_currentScene->second->Show();
}

void SceneController::Push(const std::string &name)
{
    auto iter = m_scenes.find(name);
    assert(iter != m_scenes.end() and "Push scene that hasn't been registered!");

    m_stackedScenes.push(iter->first);
    Change(name);
}

void SceneController::Pop()
{
    assert(false == m_stackedScenes.empty() and "Can't Pop scene, the stack is empty!");

    const std::string prevSceneName = m_stackedScenes.top();
    m_stackedScenes.pop();
    Change(prevSceneName);
}

void SceneController::InitScenes()
{
    for(auto& p : m_scenes)
    {
        p.second->Init();
    }
}

void SceneController::Process()
{
    m_currentScene->second->Process();
}
