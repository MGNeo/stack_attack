#pragma once

#include <SFML/Window.hpp>

#include "ResourceLibrary.hpp"

namespace sa
{
  class Scene
  {
  public:

    using Uptr = std::unique_ptr<Scene>;

    Scene(sf::RenderWindow& _render_window,
          sa::ResourceLibrary& _resource_library);

    Uptr run();

    virtual ~Scene();

  private:

    static constexpr float MAX_FPS = 60.f;
    static constexpr float MIN_FPS = 30.f;

    static constexpr float MAX_DT = 1.f / MIN_FPS;
    static constexpr float MIN_DT = 1.f / MAX_FPS;

    sf::RenderWindow& render_window;
    sa::ResourceLibrary& resource_library;

    // It's dependency inversion.
    virtual void control(const sf::Event& _event) = 0;
    virtual void process(const float _dt) = 0;
    virtual void draw(/*sa::Drawer& _drawer*/) const = 0;

  };
}