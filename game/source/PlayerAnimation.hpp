#pragma once

#include <PlayerAnimationState.hpp>

namespace sa
{
  class PlayerAnimation
  {
  public:

    PlayerAnimation();

    void stand();
    void runToLeft();
    void runToRight();
    void fall();

    void addProgress(const float _dt);

  private:

    PlayerAnimationState state;
    
    // TODO: Context for the frame accounting.
    const size_t MAX_FRAMES[(size_t)PlayerAnimationState::COUNT];

    float progress;

  };
}
