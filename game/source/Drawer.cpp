#include "Drawer.hpp"

sa::Drawer::Drawer(sf::RenderWindow& _render_window)
  :
  render_window{ _render_window }
{
}

void sa::Drawer::draw(const sf::Drawable& _drawable) const
{
  render_window.draw(_drawable);
}