#pragma once

namespace sa
{
  enum class PlayerAnimationState : size_t
  {
    STAND,
    RUN_TO_LEFT,
    RUN_TO_RIGHT,
    FALL,

    COUNT
  };
}