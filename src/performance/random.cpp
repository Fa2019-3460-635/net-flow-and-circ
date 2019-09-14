#include "random.hpp"

#include <cstdlib>
#include <ctime>

static bool s_initialized = false;

static void initialize ()
{
  std::srand(std::time(nullptr));
  s_initialized = true;
}

int Random::nonneg_int (int bound)
{
  if (!s_initialized)
    initialize();
  return std::rand() % bound;
}
