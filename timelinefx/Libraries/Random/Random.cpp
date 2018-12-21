#include "Random.h"

namespace Core
{

Random::Random() : m_engine(std::random_device()())
{

}

Random::Random(int64_t seed) : m_engine(seed)
{

}

bool Random::operator()(double probability)
{
    probability = std::max(probability, 0.0);
    probability = std::min(probability, 1.0);
    return std::bernoulli_distribution{probability}(m_engine);
}

} //end of Core
