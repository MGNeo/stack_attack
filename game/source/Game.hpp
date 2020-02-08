#pragma once

#include <ResourceLibrary.hpp>

namespace sa
{
  class Game
  {
  public:

    Game();
    void play();

  private:

    static constexpr float MAX_FPS = 200.f;
    static constexpr float MIN_FPS = 30.f;

    static constexpr float MAX_DT = 1.f / MIN_FPS;
    static constexpr float MIN_DT = 1.f / MAX_FPS;

    // sf::RenderWindow has to be created before copying of sf::Texture,
    // otherwise sf::Texture::Texture(const sf::Texutre&) has error.
    // Perhaps, it's bug.
    sf::RenderWindow render_window;
    ResourceLibrary resource_library;

  };
}
