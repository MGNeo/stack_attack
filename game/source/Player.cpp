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

size_t sa::Player::getSourceX() const
{
  return stepper.getSourceX();
}

size_t sa::Player::getSourceY() const
{
  return stepper.getSourceY();
}

size_t sa::Player::getDestinationX() const
{
  return stepper.getDestinationX();
}

size_t sa::Player::getDestinationY() const
{
  return stepper.getDestinationY();
}

float sa::Player::getRepresentedX() const
{
  return stepper.getRepresentedX();
}

float sa::Player::getRepresentedY() const
{
  return stepper.getRepresentedY();
}