#include "PlayerAnimation.hpp"

sa::PlayerAnimation::PlayerAnimation()
  :
  state{ PlayerAnimationState::STAND },
  MAX_FRAMES{ 2, 2, 2, 2 },
  progress { 0.f }
{

}

void sa::PlayerAnimation::stand()
{
  state = PlayerAnimationState::STAND;
  // ...
}

void sa::PlayerAnimation::runToLeft()
{
  state = PlayerAnimationState::RUN_TO_LEFT;
  // ...
}

void sa::PlayerAnimation::runToRight()
{
  state = PlayerAnimationState::RUN_TO_RIGHT;
  // ...
}

void sa::PlayerAnimation::fall()
{
  state = PlayerAnimationState::FALL;
  // ...
}

void sa::PlayerAnimation::addProgress(const float _dt)
{
  // ...
}