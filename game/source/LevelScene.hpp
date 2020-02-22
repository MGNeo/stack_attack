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

    void processBoxes(const float _dt);
    void generate(const float _dt);
    void boxTriesToStepToDown(Box& _box);
    void analyseBottomLine();
    void analyseSectors();
    void deleteMarkedBoxes();
    void drawBoxes(const Drawer& _drawer) const;

    void processPlayer(const float _dt);
    bool playerTriesToStepToLeft();
    bool playerTriesToStepToRight();
    bool playerTriesToStepToUp();
    bool playerTriesToStepToDown();
    void drawPlayer(const Drawer& _drawer) const;

  };
}
