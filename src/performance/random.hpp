#pragma once

class Random
{
public:
  /**
   * Returns an integer in range from [0, 'max'] (inclusive)
   * 
   * Preconditions:
   *  - 'max' shall be a positive integer. (Undefined behavior results if <= 0)
   */
  static int nonneg_int (int max);
};
