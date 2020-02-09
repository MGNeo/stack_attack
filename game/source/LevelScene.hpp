#pragma once

#include <Scene.hpp>
#include <Field.hpp>
#include <Box.hpp>
#include <Player.hpp>
#include <list>

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
    
    // LevelMechanics level_mechanics;
    // LevelRender level_render;

    Field field;
    std::list<Box> boxes;
    Player player;

  };
}
