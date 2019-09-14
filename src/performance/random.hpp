#pragma once

class Random
{
public:
  /**
   * Returns an integer in range from 0 (inclusive) to given bound (exclusive).
   * 
   * Preconditions:
   *  - 'bound' shall be a positive integer. (Undefined behavior results if bound <= 0)
   */
  static int nonneg_int (int bound);
};
