#include <Shard.hpp>

sa::Shard::Shard(const float _x,
                 const float _y,
                 const float _vx,
                 const float _vy,
                 const float _a,
                 const float _va,
                 const sf::Color _color)
  :
  x{ _x },
  y{ _y },
  vx{ _vx },
  vy{ _vy },
  a{ _a },
  va{ _va },
  color{ _color }
{
}

float sa::Shard::getX() const
{
  return x;
}

float sa::Shard::getY() const
{
  return y;
}

float sa::Shard::getA() const
{
  return a;
}

void sa::Shard::process(const float _dt)
{
  x += _dt * vx;
  y += _dt * vy;
  a -= _dt * va;
  if (a < 0.f)
  {
    a = 0.f;
  }
}

sf::Color sa::Shard::getColor() const
{
  return color;
}