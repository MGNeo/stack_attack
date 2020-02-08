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

bool sa::Stepper::isReady() const
{
  if (progress == MAX_PROGRESS)
  {
    return true;
  } else {
    return false;
  }
}

void sa::Stepper::toLeft()
{
  if (isReady() == false)
  {
    throw std::logic_error("sa::Stepper::toLeft(), isReady() == false");
  }

  previous_x = next_x;
  previous_y = next_y;

  if (next_x > 0)
  {
    --next_x;
  }

  progress = 0.f;
}

void sa::Stepper::toRight()
{
  if (isReady() == false)
  {
    throw std::logic_error("sa::Stepper::toRight(), isReady() == false");
  }

  previous_x = next_x;
  previous_y = next_y;

  if (next_x < SIZE_MAX)
  {
    ++next_x;
  }

  progress = 0.f;
}

void sa::Stepper::toUp()
{
  if (isReady() == false)
  {
    throw std::logic_error("sa::Stepper::toUp(), isReady() == false");
  }

  previous_x = next_x;
  previous_y = next_y;

  if (next_y > 0)
  {
    --next_y;
  }

  progress = 0.f;
}

void sa::Stepper::toDown()
{
  if (isReady() == false)
  {
    throw std::logic_error("sa::Stepper::toLeft(), isDown() == false");
  }

  previous_x = next_x;
  previous_y = next_y;

  if (next_y < SIZE_MAX)
  {
    ++next_x;
  }

  progress = 0.f;
}