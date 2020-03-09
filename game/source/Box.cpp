#include <Box.hpp>

sa::Box::Box(const ptrdiff_t _x,
             const ptrdiff_t _y,
             const float _speed,
             const sf::Color _color)
  :
  Stepper{ _x, _y, _speed },
  color{ _color },
  mark{ false }
{
}

const sf::Color& sa::Box::getColor() const
{
  return color;
}

bool sa::Box::isMarked() const
{
  return mark;
}

void sa::Box::toMark()
{
    mark = true;
}