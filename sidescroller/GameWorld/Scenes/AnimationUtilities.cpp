#include "AnimationUtilities.h"
#include <GameFramework/Framework/Context.hpp>
#include <GameFramework/Framework/ResourcesMgr.h>
#include <CharacterParser/CharacterParser.h>

std::vector<std::string> utilities::GetAnimationFrames(const std::string& name, const std::string& animId)
{
    const auto& parser = Context::Get<Parser::CharacterParser>();
    std::vector<std::string> result;
    for(auto& key : parser.GetTexturePaths(name, animId))
    {
        result.push_back(key);
    }
    return result;
}
