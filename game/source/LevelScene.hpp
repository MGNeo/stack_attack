#pragma once

#include <Scene.hpp>
#include <LevelSceneData.hpp>
#include <LevelSceneProcessHandler.hpp>
#include <LevelSceneDrawHandler.hpp>

namespace sa
{
  class LevelScene : public Scene
  {
  public:

    LevelScene(ResourceLibrary& _resource_library);

    void react(const sf::Event& _event) override;
    void process(const float _dt) override;
    void draw(const Drawer& _drawer) const override;

    Uptr getNextScene() override;

  private:

    LevelSceneData data;
    // TODO: Add ReactHandler if it is necessary.
    LevelSceneProcessHandler process_handler;
    LevelSceneDrawHandler draw_handler;
  };

}
