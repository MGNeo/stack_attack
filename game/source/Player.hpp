#pragma once

#include <Stepper.hpp>
#include <PlayerAnimation.hpp>

namespace sa
{
  class Player
  {
  public:

    Player(const ptrdiff_t _x, const ptrdiff_t _y);

    bool isReadyToStep() const;

    void stepToLeft();
    void stepToRight();
    void stepToUp();
    void stepToDown();
    void fix();

    ptrdiff_t getSourceX() const;
    ptrdiff_t getSourceY() const;

    ptrdiff_t getDestinationX() const;
    ptrdiff_t getDestinationY() const;

    float getRepresentedX() const;
    float getRepresentedY() const;

    void process(const float _dt);

  public:

    // In our case it's better to use composition.
    Stepper stepper;
    PlayerAnimation animation;

  };
}
