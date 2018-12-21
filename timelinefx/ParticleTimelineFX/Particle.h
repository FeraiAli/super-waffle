#pragma once
#include <SFML/System/Vector2.hpp>
#include <string>
#include <vector>

namespace sf { class RenderWindow; }
namespace fx
{
    enum class Effect
    {
        Explosion_Blast1,
        Explosion_Blast2,
        Explosion_Blast3,
        Explosion_Blast4,
        Explosion_Cloud1,
        Explosion_Cloud2,
        Explosion_Cloud3,
        Explosion_Debrie1,
        Explosion_COUNT,

    };

    void Emit(Effect effect, sf::Vector2f pos, float scale = 1.0f);

    void Init(sf::RenderWindow& window);
    void Deinit();

namespace debug
{
    //Will load all valid effect names from (dataFileName) and inspect them
    //All effects that you like can be saved into (outputDir)
    void Inspect(const std::string& dataFileName, const std::string& outputDir,
                 std::vector<int> ignoreIndecies = {});
}

}
