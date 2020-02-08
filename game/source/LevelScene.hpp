#pragma once

#include <Scene.hpp>
#include <LevelResources.hpp>
#include <Field.hpp>

namespace sa
{
  class LevelScene : public Scene
  {
  public:

    LevelScene(ResourceLibrary& _resource_library);

    void control(const sf::Event& _event) override;
    void process(const float _dt) override;
    void draw(const Drawer& _drawer) const override;

    Uptr getNextScene() override;

  private:

    LevelResources level_resources;

    Field field;


  };
}
