#pragma once

#include "Scene.hpp"

namespace sa
{
  class LevelScene : public Scene
  {
  public:

    LevelScene(sa::ResourceLibrary& _resource_library);

    void control(const sf::Event& _event) override;
    void process(const float _dt) override;
    void draw(const sa::Drawer& _drawer) const override;

    virtual Uptr getNextScene() override;

  };
}
