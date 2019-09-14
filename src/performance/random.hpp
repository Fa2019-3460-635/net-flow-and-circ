#pragma once

class Random
{
public:
  /**
   * Returns an integer in range from ['min', 'max'] (inclusive)
   * 
   * Preconditions:
   *  - 0 <= min <= max
   */
  static int nonneg_int (int min, int max);
};
