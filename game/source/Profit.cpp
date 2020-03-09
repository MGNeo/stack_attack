#include <Profit.hpp>

sa::Profit::Profit(const size_t _count,
                   const float _x,
                   const float _y,
                   const float _va)
  :
  count{ _count },
  x{ _x },
  y{ _y },
  a{ 1.f },
  va{ _va }
{
}

size_t sa::Profit::getCount() const
{
  return count;
}

float sa::Profit::getX() const
{
  return x;
}

float sa::Profit::getY() const
{
  return y;
}

float sa::Profit::getA() const
{
  return a;
}


void sa::Profit::process(const float _dt)
{
  a -= _dt * va;
  if (a < 0.f)
  {
    a = 0.f;
  }
}