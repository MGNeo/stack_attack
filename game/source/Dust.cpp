#include <Dust.hpp>

sa::Dust::Dust(const float _x, const float _y)
  :
  x{ _x },
  y{ _y }
{
}

float sa::Dust::getX() const
{
  return x;
}

float sa::Dust::getY() const
{
  return y;
}

void sa::Dust::setX(const float _x)
{
  x = _x;
}

void sa::Dust::setY(const float _y)
{
  y = _y;
}