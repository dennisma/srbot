#pragma once


/// @brief acts like arduino map - maps from imin imax to omin omax
/// @tparam T a numeric types (double, int, etc)
/// @param x the value to mape
/// @param imin the input min val
/// @param imax the input max val 
/// @param omin the output min value
/// @param omax the output max value
/// @return the mapped value of x
template <typename T>
T mapfunc(T x, T imin, T imax, T omin, T omax)
{
  return (x - imin) * (omax - omin) / (imax - imin) + omin;
}

/// @brief constrains a value between a min and max
/// @tparam T a numeric type
/// @param val the value to constrain
/// @param min the minimum constraint 
/// @param max the maxiumum constraint
/// @return if val > max, return max.  if val < min, return min.  Otherwise return val
template <typename T>
T constrain_t(T val, T min, T max)
{
  if (val < min)
    return min;
  if (val > max)
    return max;
  return val;
}

/// @brief combo of both constrain and map 
/// @tparam T a numeric type
/// @param x the value to mape
/// @param imin the input min val
/// @param imax the input max val 
/// @param omin the output min value
/// @param omax the output max value
/// @return the mapped value of x but constrained between omin and omax
template <typename T>
T cmap(T x, T imin, T imax, T omin, T omax)
{
  return constrain_t(mapfunc(x, imin, imax, omin, omax),
                   omin,
                   omax);
}

