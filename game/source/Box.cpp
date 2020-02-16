#include <Box.hpp>

sa::Box::Box(const size_t _x, const size_t _y, const sf::Color _color)
  :
  Stepper{ _x, _y },
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