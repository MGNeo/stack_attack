#pragma once

#include <Stepper.hpp>
#include <PlayerAnimation.hpp>

namespace sa
{
  class Player
  {
  public:

    Player(const size_t _x, const size_t _y);

    bool isReadyToStep() const;

    void stepToLeft();
    void stepToRight();
    void stepToUp();
    void stepToDown();
    void fix();

    size_t getSourceX() const;
    size_t getSourceY() const;

    size_t getDestinationX() const;
    size_t getDestinationY() const;

    float getRepresentedX() const;
    float getRepresentedY() const;

    void process(const float _dt);

  public:

    // In our case it's better to use composition.
    Stepper stepper;
    PlayerAnimation animation;

  };
}
