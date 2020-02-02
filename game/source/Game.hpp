#pragma once

#include "ResourceLibrary.hpp"

namespace sa
{
  class Game
  {
  public:
    Game();
    void play();
  private:
    // sf::RenderWindow has to be created before copying of sf::Texture,
    // otherwise sf::Texture::Texture(const sf::Texutre&) has error.
    // Perhaps, it's bug.
    sf::RenderWindow render_window;

    sa::ResourceLibrary resource_library;
  };
}
