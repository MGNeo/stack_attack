#include <Delivery.hpp>
#include <stdexcept>

sa::Delivery::Delivery(const ptrdiff_t _source, const ptrdiff_t _destination, const ptrdiff_t _target)
  :
  source{ _source },
  destination{ _destination },
  target{ _target },
  current{ _source },
  progress{ MAX_PROGRESS }
{
  if (source == destination)
  {
    throw std::invalid_argument("sa::Delivery::Delivery(), source == destination.");
  }

  if (source < destination)
  {
    if (target < source)
    {
      throw std::invalid_argument("sa::Delivery::Delivery(), target < source.");
    }
    if (target > destination)
    {
      throw std::invalid_argument("sa::Delivery::Delivery(), target > destination.");
    }
  } else {
    if (target > source)
    {
      throw std::invalid_argument("sa::Delivery::Delivery(), target > source.");
    }
    if (target < destination)
    {
      throw std::invalid_argument("sa::Delivery::Delivery(), target < destination.");
    }
  }
}

bool sa::Delivery::isReadyToStep() const
{
  return (progress == MAX_PROGRESS);
}

void sa::Delivery::step()
{
  if (isReadyToStep() == false)
  {
    throw std::logic_error("sa::Delivery::step(), isReadyToStep() == false.");
  }

  if (target != destination)
  {
    if (source < destination)
    {
      if (current < PTRDIFF_MAX)
      {
        ++current;
        progress = MIN_PROGRESS;
        return;
      }
    } else {
      if (current > PTRDIFF_MIN)
      {
        --current;
        progress = MIN_PROGRESS;
        return;
      }
    }
  }
}

void sa::Delivery::process(const float _dt)
{
  progress += _dt;
  if (progress > MAX_PROGRESS)
  {
    progress = MAX_PROGRESS;
  }
}

ptrdiff_t sa::Delivery::getCurrent() const
{
  return current;
}

float sa::Delivery::getRepresentedCurrent() const
{
  if (source < destination)
  {
    return static_cast<float>(current) + progress;
  } else {
    return static_cast<float>(current) - progress;
  }
}

bool sa::Delivery::isReadyToThrow() const
{
  if (isReadyToStep() == true)
  {
    if (current == target)
    {
      return true;
    }
  }

  return false;
}

bool sa::Delivery::isFinish() const
{
  if (isReadyToStep() == true)
  {
    if (current == destination)
    {
      return true;
    }
  }
  return false;
}