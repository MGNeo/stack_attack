#pragma once

#include <list>

namespace sa
{
  class Profit
  {
  public:

    using List = std::list<Profit>;

    Profit(const size_t _count,
           const float _x,
           const float _y,
           const float _va);

    size_t getCount() const;

    float getX() const;
    float getY() const;

    float getA() const;

    void process(const float _dt);

  private:

    size_t count;

    float x;
    float y;

    float a;
    const float va;

  };
}
