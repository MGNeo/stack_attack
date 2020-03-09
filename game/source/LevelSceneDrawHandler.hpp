#pragma once

#include <ResourceLibrary.hpp>
#include <LevelSceneData.hpp>
#include <Drawer.hpp>

namespace sa
{
  class LevelSceneDrawHandler
  {
  public:

    LevelSceneDrawHandler(ResourceLibrary& _resource_library,
                          const Drawer& _drawer,
                          LevelSceneData& _data,
                          const GameSettings& _game_settings);

    void draw() const;

  private:

    ResourceLibrary& resource_library;
    const Drawer& drawer;
    LevelSceneData& data;
    const GameSettings& game_settings;

    void drawBoxes() const;
    void drawDeliveries() const;
    void drawShards() const;
    void drawProfits() const;
    void drawPlayer() const;

  };
}
