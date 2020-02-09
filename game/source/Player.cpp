#include <Player.hpp>

sa::Player::Player(const size_t _x, const size_t _y)
  :
  Stepper{ _x, _y }
{
}

void sa::Player::stepToLeft()
{
  Stepper::stepToLeft();
  // ...
}

void sa::Player::stepToRight()
{
  Stepper::stepToRight();
  // ...
}

void sa::Player::stepToUp()
{
  Stepper::stepToUp();
  // ...
}

void sa::Player::stepToDown()
{
  Stepper::stepToDown();
  // ...
}

void sa::Player::addProgress(const float _dt)
{
  Stepper::addProgress(_dt);
  // ...
}