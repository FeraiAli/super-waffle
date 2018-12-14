#pragma once
#include <timelinefx_parser/TLFXEffectsLibrary.h>
#include <vector>

class EffectLibrary : public TLFX::EffectsLibrary
{
public:
    TLFX::XMLLoader* CreateLoader() const override;
    TLFX::AnimImage* CreateImage() const override;

    std::vector<std::string> GetAllEffectsName() const;
private:
};
