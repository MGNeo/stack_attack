#pragma once

#include <Stepper.hpp>
#include <Drawer.hpp>

namespace sa
{
  class Player
  {
  public:

    Player(const size_t _x, const size_t _y);

    Stepper& getStepper();

    void draw(const Drawer& _drawer) const;

  private:

    Stepper stepper;

  };
}
