#pragma once

#include <SFML/Graphics.hpp>
#include <list>

namespace sa
{
  class Shard
  {
  public:

    using List = std::list<Shard>;

    Shard(const float _x,
          const float _y,
          const float _vx,
          const float _vy,
          const float _a,
          const float _va,
          const sf::Color _color);

    float getX() const;
    float getY() const;

    float getA() const;

    void updatePosition(const float _dt);
    void updateAlpha(const float _dt);

    sf::Color getColor() const;

  private:

    float x;
    float y;

    float vx;
    float vy;

    float a;
    const float va;

    const sf::Color color;

  };
}
