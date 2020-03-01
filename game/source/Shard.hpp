#pragma once

#include <SFML/Graphics.hpp>
#include <list>

namespace sa
{
  class Shard
  {
  public:

    using List = std::list<Shard>;

    Shard(const float _x, const float _y,
          const float _vx, const float _vy,
          const float _a,
          const float _av,
          const sf::Color _color);

    float getX() const;
    float getY() const;

    void setX(const float _x);
    void setY(const float _y);

    float getVX() const;
    float getVY() const;

    void setVX(const float _vx);
    void setVY(const float _vy);

    float getA() const;
    void reduceA(const float _dt);

    sf::Color getColor() const;

  private:

    float x;
    float y;

    float vx;
    float vy;

    float a;
    const float av;

    const sf::Color color;

  };
}
