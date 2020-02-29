#pragma once

#include <Particle.hpp>

namespace sa
{
  class Dust : public Particle
  {
  public:

    Dust(const float _x, const float _y);


    float getX() const;
    float getY() const;

    void setX(const float _x);
    void setY(const float _y);

  private:

    float x;
    float y;

  };
}
