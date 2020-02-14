#include <Player.hpp>

sa::Player::Player(const size_t _x, const size_t _y)
  :
  stepper{ _x, _y }
{
}

bool sa::Player::isReadyToStep() const
{
  return stepper.isReadyToStep();
}

void sa::Player::stepToLeft()
{
  stepper.stepToLeft();
  animation.runToLeft();
}

void sa::Player::stepToRight()
{
  stepper.stepToRight();
  animation.runToRight();
}

void sa::Player::stepToUp()
{
  stepper.stepToUp();
  animation.fall();
}

void sa::Player::stepToDown()
{
  stepper.stepToDown();
  animation.fall();
}

void sa::Player::fix()
{
  stepper.fix();
  animation.stand();
}

void sa::Player::process(const float _dt)
{
  stepper.process(_dt);
  animation.process(_dt);

  if (stepper.isReadyToStep() == true)
  {
    animation.stand();
  }
}

size_t sa::Player::getPreviousX() const
{
  return stepper.getPreviousX();
}

size_t sa::Player::getPreviousY() const
{
  return stepper.getPreviousY();
}

size_t sa::Player::getNextX() const
{
  return stepper.getNextX();
}

size_t sa::Player::getNextY() const
{
  return stepper.getNextY();
}

float sa::Player::getX() const
{
  return stepper.getX();
}

float sa::Player::getY() const
{
  return stepper.getY();
}