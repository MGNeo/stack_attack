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

    size_t getPreviousX() const;
    size_t getPreviousY() const;

    size_t getNextX() const;
    size_t getNextY() const;

    float getX() const;
    float getY() const;

    void addProgress(const float _dt);

  public:

    // In our case it's better to use composition.
    Stepper stepper;
    PlayerAnimation animation;

  };
}
