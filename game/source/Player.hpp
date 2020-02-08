#pragma once

#include <Stepper.hpp>
#include <Drawer.hpp>

namespace sa
{
  class Player : public Stepper
  {
  public:

    Player(const size_t _x, const size_t _y);

    void progress(const float _dt);

    void draw(const Drawer& _drawer) const;

  };
}
