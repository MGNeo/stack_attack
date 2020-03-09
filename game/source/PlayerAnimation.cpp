#include "PlayerAnimation.hpp"

sa::PlayerAnimation::PlayerAnimation(const float _speed)
  : 
  speed{ _speed },
  SEQUENCES_LENGTHS{ 2, 2, 2, 2 },
  state{ PlayerAnimationState::STAND },
  progress { 0.f }
{
}

void sa::PlayerAnimation::stand()
{
  state = PlayerAnimationState::STAND;
  progress = 0.f;
}

void sa::PlayerAnimation::runToLeft()
{
  state = PlayerAnimationState::RUN_TO_LEFT;
  progress = 0.f;
}

void sa::PlayerAnimation::runToRight()
{
  state = PlayerAnimationState::RUN_TO_RIGHT;
  progress = 0.f;
}

void sa::PlayerAnimation::fall()
{
  state = PlayerAnimationState::FALL;
  progress = 0.f;
}

void sa::PlayerAnimation::update(const float _dt)
{
  progress += speed * _dt;
  if (progress > SEQUENCES_LENGTHS[static_cast<size_t>(state)])
  {
    progress = 0.f;
  }
}