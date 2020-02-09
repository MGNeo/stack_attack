#include <Box.hpp>

sa::Box::Box(const size_t _x, const size_t _y, const sf::Color _color)
  :
  Stepper{ _x, _y },
  color{ _color }
{
}

const sf::Color& sa::Box::getColor() const
{
  return color;
}
