#include <Cell.hpp>

sa::Cell::Cell()
  :
  busy{ false }
{
}

bool sa::Cell::getBusy() const
{
  return busy;
}

void sa::Cell::setBusy(const bool _busy)
{
  busy = _busy;
}