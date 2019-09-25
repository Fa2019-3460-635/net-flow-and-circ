#pragma once

#include <chrono>

class Timer
{
public:
  /**
   * Constructs a timer, caching the "time of construction".
   */
  Timer ();

  /**
   * Returns the number of milliseconds that have elapsed since the timer's
   * "time of construction".
   */
  double milliseconds () const;

private:
  std::chrono::time_point<std::chrono::steady_clock> time_of_construction;
};