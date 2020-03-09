#pragma once

#include <PlayerAnimationState.hpp>

namespace sa
{
  class PlayerAnimation
  {
  public:

    PlayerAnimation(const float _speed = 1.f);

    void stand();
    void runToLeft();
    void runToRight();
    void fall();

    void updateProgress(const float _dt);

  private:

    const float speed;

    const size_t SEQUENCES_LENGTHS[(size_t)PlayerAnimationState::COUNT];

    PlayerAnimationState state;

    float progress;

  };
}
