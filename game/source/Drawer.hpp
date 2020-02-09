#pragma once

#include <SFML/Graphics.hpp>

namespace sa
{
  // The limiting proxy for drawing.
  class Drawer
  {
  public:

    Drawer(sf::RenderWindow& _render_window);

    void draw(const sf::Drawable& _drawable) const;

    size_t getWindowWidth() const;
    size_t getWindowHeight() const;

  private:

    sf::RenderWindow& render_window;

  };
}