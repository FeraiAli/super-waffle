#pragma once
#include <memory>

namespace Entita
{

class BaseSystem
{
public:
    using Ptr = std::shared_ptr<BaseSystem>;
    virtual ~BaseSystem() = default;

    virtual void Init(){}
    virtual void Process() = 0;
};

} // end of namespace Entita

