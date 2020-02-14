#pragma once

#include <SFML/Window.hpp>

#include <ResourceLibrary.hpp>
#include <Drawer.hpp>

namespace sa
{
  class Scene
  {
  public:

    using Uptr = std::unique_ptr<Scene>;

    Scene(ResourceLibrary& _resource_library);

    virtual bool isActive() const;
    
    virtual void react(const sf::Event& _event) = 0;
    virtual void process(const float _dt) = 0;
    virtual void draw(const Drawer& _drawer) const = 0;
    
    virtual Uptr getNextScene() = 0;

    virtual ~Scene();

  protected:

    ResourceLibrary& resource_library;

  };
}