#include <Cell.hpp>

sa::Cell::Cell()
  :
  occupyingBox{ nullptr }
{
}

sa::Box* sa::Cell::getOccupyingBox() const
{
  return occupyingBox;
}

void sa::Cell::setOccupingBox(Box*const _occupyingBox)
{
  occupyingBox = _occupyingBox;
}