#include "timer.hpp"

Timer::Timer ()
{
  time_of_construction = std::chrono::steady_clock::now();
}

double Timer::milliseconds () const
{
  static double const NANOSECONDS_2_MILLISECONDS = 1.0 / 1000000;
  auto now = std::chrono::steady_clock::now();
  auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(now - time_of_construction).count();
  return nanoseconds * NANOSECONDS_2_MILLISECONDS;
}