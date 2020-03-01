#include <Shard.hpp>

sa::Shard::Shard(const float _x, const float _y,
                 const float _vx, const float _vy,
                 const float _a,
                 const float _av,
                 const sf::Color _color)
  :
  x{ _x },
  y{ _y },
  vx{ _vx },
  vy{ _vy },
  a{ _a },
  av{ _av },
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

void sa::Shard::setX(const float _x)
{
  x = _x;
}

void sa::Shard::setY(const float _y)
{
  y = _y;
}

float sa::Shard::getVX() const
{
  return vx;
}

float sa::Shard::getVY() const
{
  return vy;
}

void sa::Shard::setVX(const float _vx)
{
  vx = _vx;
}

void sa::Shard::setVY(const float _vy)
{
  vy = _vy;
}

float sa::Shard::getA() const
{
  return a;
}

void sa::Shard::reduceA(const float _dt)
{
  a -= _dt * av;
  if (a < 0.f)
  {
    a = 0.f;
  }
}

sf::Color sa::Shard::getColor() const
{
  return color;
}