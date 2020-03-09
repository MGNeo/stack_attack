#pragma once

#include <Scene.hpp>
#include <LevelSceneData.hpp>
#include <LevelSceneUpdateHandler.hpp>
#include <LevelSceneDrawHandler.hpp>

namespace sa
{
  class LevelScene : public Scene
  {
  public:

    LevelScene(ResourceLibrary& _resource_library,
               const Drawer& _drawer,
               const GameSettings& _game_settings);

    void react(const sf::Event& _event) override;
    void update(const float _dt) override;
    void draw() const override;

    Uptr getNextScene() override;

  private:

    LevelSceneData data;
    // TODO: Add ReactHandler if it is necessary.
    LevelSceneUpdateHandler update_handler;
    LevelSceneDrawHandler draw_handler;
  };

}
