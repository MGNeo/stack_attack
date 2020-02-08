#include <Stepper.hpp>
#include <stdexcept>

sa::Stepper::Stepper(const size_t _x, const size_t _y)
  :
  previous_x{ _x },
  previous_y{ _y },
  next_x{ _x },
  next_y{ _y },
  progress{ MAX_PROGRESS }
{
}

void sa::Stepper::addProgress(const float _progress)
{
  progress += _progress;
  if (progress > MAX_PROGRESS)
  {
    progress = MAX_PROGRESS;
  }
}

bool sa::Stepper::isReadyToStep() const
{
  if (progress == MAX_PROGRESS)
  {
    return true;
  } else {
    return false;
  }
}

void sa::Stepper::stepToLeft()
{
  if (isReadyToStep() == false)
  {
    throw std::logic_error("sa::Stepper::stepToLeft(), isReady() == false");
  }

  previous_x = next_x;
  previous_y = next_y;

  if (next_x > 0)
  {
    --next_x;
  }

  progress = 0.f;
}

void sa::Stepper::stepToRight()
{
  if (isReadyToStep() == false)
  {
    throw std::logic_error("sa::Stepper::stepToRight(), isReady() == false");
  }

  previous_x = next_x;
  previous_y = next_y;

  if (next_x < SIZE_MAX)
  {
    ++next_x;
  }

  progress = 0.f;
}

void sa::Stepper::stepToUp()
{
  if (isReadyToStep() == false)
  {
    throw std::logic_error("sa::Stepper::stepToUp(), isReady() == false");
  }

  previous_x = next_x;
  previous_y = next_y;

  if (next_y > 0)
  {
    --next_y;
  }

  progress = 0.f;
}

void sa::Stepper::stepToDown()
{
  if (isReadyToStep() == false)
  {
    throw std::logic_error("sa::Stepper::stepToDown(), isDown() == false");
  }

  previous_x = next_x;
  previous_y = next_y;

  if (next_y < SIZE_MAX)
  {
    ++next_y;
  }

  progress = 0.f;
}

size_t sa::Stepper::getPreviousX() const
{
  return previous_x;
}

size_t sa::Stepper::getPreviousY() const
{
  return previous_y;
}

size_t sa::Stepper::getNextX() const
{
  return next_x;
}

size_t sa::Stepper::getNextY() const
{
  return next_y;
}

float sa::Stepper::getX() const
{
  if (previous_x < next_x)
  {
    return previous_x + progress;
  }
  if (previous_x > next_x)
  {
    return previous_x - progress;
  }
  return static_cast<float>(next_x);
}

float sa::Stepper::getY() const
{
  if (previous_y < next_y)
  {
    return previous_y + progress;
  }
  if (previous_y > next_y)
  {
    return previous_y - progress;
  }
  return static_cast<float>(next_y);
}