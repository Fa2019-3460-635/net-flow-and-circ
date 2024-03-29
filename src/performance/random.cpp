#include "random.hpp"

#include <cassert>
#include <ctime>
#include <random>

static std::default_random_engine s_engine;
static bool s_initialized = false;

static void initialize ()
{
  s_engine.seed(std::time(nullptr));
  s_initialized = true;
}

int Random::nonneg_int (int min, int max)
{
  assert(0 <= min && min <= max);
  if (!s_initialized)
    initialize();
  std::uniform_int_distribution<int> distribution(min, max);
  return distribution(s_engine);
}
