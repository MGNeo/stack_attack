#pragma once

#include <SFML/Window.hpp>

#include "ResourceLibrary.hpp"
#include "Drawer.hpp"

namespace sa
{
  class Scene
  {
  public:

    using Uptr = std::unique_ptr<Scene>;

    Scene(sa::ResourceLibrary& _resource_library);

    bool isActive() const;
    
    virtual void control(const sf::Event& _event) = 0;
    virtual void process(const float _dt) = 0;
    virtual void draw(const sa::Drawer& _drawer) const = 0;
    
    virtual Uptr getNextScene() = 0;

    virtual ~Scene();

  protected:

    void disable();

  private:

    bool active;

    sa::ResourceLibrary& resource_library;

  };
}