#include <Stepper.hpp>
#include <stdexcept>

sa::Stepper::Stepper(const size_t _x, const size_t _y)
  :
  source_x{ _x },
  source_y{ _y },
  destination_x{ _x },
  destination_y{ _y },
  progress{ MAX_PROGRESS }
{
}

void sa::Stepper::process(const float _progress)
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
    throw std::logic_error("sa::Stepper::stepToLeft(), isReadyToStep() == false.");
  }

  source_x = destination_x;
  source_y = destination_y;

  if (destination_x > 0u)
  {
    --destination_x;
  }

  progress = 0.f;
}

void sa::Stepper::stepToRight()
{
  if (isReadyToStep() == false)
  {
    throw std::logic_error("sa::Stepper::stepToRight(), isReadyToStep() == false.");
  }

  source_x = destination_x;
  source_y = destination_y;

  if (destination_x < SIZE_MAX)
  {
    ++destination_x;
  }

  progress = 0.f;
}

void sa::Stepper::stepToUp()
{
  if (isReadyToStep() == false)
  {
    throw std::logic_error("sa::Stepper::stepToUp(), isReadyToStep() == false.");
  }

  source_x = destination_x;
  source_y = destination_y;

  if (destination_y > 0)
  {
    --destination_y;
  }

  progress = 0.f;
}

void sa::Stepper::stepToDown()
{
  if (isReadyToStep() == false)
  {
    throw std::logic_error("sa::Stepper::stepToDown(), isReadyToStep() == false.");
  }

  source_x = destination_x;
  source_y = destination_y;

  if (destination_y < SIZE_MAX)
  {
    ++destination_y;
  }

  progress = 0.f;
}

void sa::Stepper::fix()
{
  if (isReadyToStep() == false)
  {
    throw std::logic_error("sa::Stepper::fix(), isReadyToStep() == false.");
  }

  source_x = destination_x;
  source_y = destination_y;
}

size_t sa::Stepper::getSourceX() const
{
  return source_x;
}

size_t sa::Stepper::getSourceY() const
{
  return source_y;
}

size_t sa::Stepper::getDestinationX() const
{
  return destination_x;
}

size_t sa::Stepper::getDestinationY() const
{
  return destination_y;
}

float sa::Stepper::getRepresentedX() const
{
  if (source_x < destination_x)
  {
    return source_x + progress;
  }
  if (source_x > destination_x)
  {
    return source_x - progress;
  }
  return static_cast<float>(destination_x);
}

float sa::Stepper::getRepresentedY() const
{
  if (source_y < destination_y)
  {
    return source_y + progress;
  }
  if (source_y > destination_y)
  {
    return source_y - progress;
  }
  return static_cast<float>(destination_y);
}
