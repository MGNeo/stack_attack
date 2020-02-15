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

    void react(const sf::Event& _event) override;
    void process(const float _dt) override;
    void draw(const Drawer& _drawer) const override;

    Uptr getNextScene() override;

  private:

    Field field;
    std::list<Box> boxes;
    Player player;

    void controlBoxes();
    void controlPlayer();

    bool playerTriesToStepToLeft();
    bool playerTriesToStepToRight();
    bool playerTriesToStepToUp();
    bool playerTriesToStepToDown();

    void processBoxes(const float _dt);
    void processPlayer(const float _dt);

    void drawBoxes(const Drawer& _drawer) const;
    void drawPlayer(const Drawer& _drawer) const;

  };
}
