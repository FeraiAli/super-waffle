#pragma once
#include <memory>

class IScene
{
public:
    using uPtr = std::unique_ptr<IScene>;

    IScene() = default;
    virtual ~IScene() = default;

    virtual void Init() = 0;
    virtual void Deinit() = 0;

    virtual void Show() = 0;
    virtual void Hide() = 0;

    virtual void Process() = 0;
};
