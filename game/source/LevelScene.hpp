#pragma once

#include "Scene.hpp"

namespace sa
{
  class LevelScene : public Scene
  {
  public:
    LevelScene(sf::RenderWindow& _render_window,
               sa::ResourceLibrary& _resource_library);
  private:
    void control(const sf::Event& _event) override;
    void process(const float _dt) override;
    void draw(/*sa::Drawer& _drawer*/) const override;
  };
}
