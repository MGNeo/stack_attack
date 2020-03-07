#pragma once

#include <SFML/Window.hpp>

#include <ResourceLibrary.hpp>
#include <Drawer.hpp>
#include <GameSettings.hpp>

namespace sa
{
  class Scene
  {
  public:

    Scene(ResourceLibrary& _resource_library,
          const Drawer& _drawer,
          const GameSettings& _game_settings);

    using Uptr = std::unique_ptr<Scene>;

    virtual bool isActive() const;
    
    virtual void react(const sf::Event& _event) = 0;
    virtual void process(const float _dt) = 0;
    virtual void draw() const = 0;
    
    virtual Uptr getNextScene() = 0;

    virtual ~Scene();

  protected:
    
    ResourceLibrary& resource_library;
    const Drawer& drawer;
    const GameSettings& game_settings;

  };
}