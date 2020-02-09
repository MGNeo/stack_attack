#pragma once

#include <Stepper.hpp>
#include <PlayerAnimation.hpp>

namespace sa
{
  class Player : public Stepper
  {
  public:

    Player(const size_t _x, const size_t _y);

    void stepToLeft() override;
    void stepToRight() override;
    void stepToUp() override;
    void stepToDown() override;

    void addProgress(const float _dt) override;

  public:

    PlayerAnimation animation;

  };
}
