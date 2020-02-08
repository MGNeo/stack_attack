#include <Player.hpp>

sa::Player::Player(const size_t _x, const size_t _y)
  :
  Stepper{ _x, _y }
{
}

void sa::Player::progress(const float _dt)
{
  addProgress(_dt);
}

void sa::Player::draw(const Drawer& _drawer) const
{
  sf::CircleShape circle;
  circle.setRadius(16);
  circle.setPosition(getX() * 32.f, getY() * 32.f);
  _drawer.draw(circle);
}