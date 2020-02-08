#include <Player.hpp>

sa::Player::Player(const size_t _x, const size_t _y)
  :
  stepper{ _x, _y }
{
}

sa::Stepper& sa::Player::getStepper()
{
  return stepper;
}

void sa::Player::draw(const Drawer& _drawer) const
{
  sf::CircleShape circle;
  circle.setRadius(32);
  circle.setPosition(stepper.getX() * 32, stepper.getY() * 32);
  _drawer.draw(circle);
}