#include "EffectLibrary.h"
#include <DataParser/TLFXPugiXMLLoader.h>
#include <DataParser/TLFXEffect.h>
#include "Image.h"

TLFX::XMLLoader* EffectLibrary::CreateLoader() const
{
    return new TLFX::PugiXMLLoader(0);
}

TLFX::AnimImage* EffectLibrary::CreateImage() const
{
    return new Image();
}

std::vector<std::string> EffectLibrary::GetAllEffectsName() const
{
    std::vector<std::string> names;
    for(auto& p : _effects)
    {
        if(p.second != nullptr)
        {
            names.push_back(p.first);
        }
    }
    return names;
}
