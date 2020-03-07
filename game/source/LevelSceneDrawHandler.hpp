#pragma once

#include <ResourceLibrary.hpp>
#include <LevelSceneData.hpp>
#include <Drawer.hpp>

namespace sa
{
  class LevelSceneDrawHandler
  {
  public:

    LevelSceneDrawHandler(LevelSceneData& _data);

    void draw(const sa::Drawer& _drawer) const;

  private:

    LevelSceneData& data;

    void drawBoxes(const Drawer& _drawer) const;
    void drawDeliveries(const Drawer& _drawer) const;
    void drawShards(const Drawer& _drawer) const;
    void drawPlayer(const Drawer& _drawer) const;


  };
}
