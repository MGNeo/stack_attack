#pragma once

#include <LevelSceneDrawSubsystemLinks.hpp>
#include <Drawer.hpp>

namespace sa
{
  class LevelSceneDrawSubsystem
  {
  public:

    LevelSceneDrawSubsystem(const LevelSceneDrawSubsystemLinks& _links);

    void draw(const Drawer& _drawer) const;

  private:

    const LevelSceneDrawSubsystemLinks links;

    void drawDeliveries(const Drawer& _drawer) const;
    void drawBoxes(const Drawer& _drawer) const;
    void drawPlayer(const Drawer& _drawer) const;

  };
}
