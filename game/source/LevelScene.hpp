#pragma once

#include <Scene.hpp>
#include <Field.hpp>
#include <Delivery.hpp>
#include <Box.hpp>
#include <Player.hpp>
#include <list>
#include <random>
#include <LevelSceneDrawSubsystem.hpp>
#include <LevelSceneDrawSubsystemLinks.hpp>

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

    const sf::Color NON_MOVABLE_COLOR;

    Field field;
    Delivery::List deliveries;
    Box::List boxes;
    Player player;

    LevelSceneDrawSubsystem draw_subsystem;

    void processDeliveries(const float _dt);
    void generateDelivery(const float _dt);
    void analyseTargetOfDelivery(Delivery& _delivery);
    void checkFinishOfDeliveries();

    void processBoxes(const float _dt);
    void boxTriesToStepToDown(Box& _box);
    void analyseBottomLine();
    void analyseSectors();
    void deleteMarkedBoxes();

    void processPlayer(const float _dt);
    bool playerTriesToStepToLeft();
    bool playerTriesToStepToRight();
    bool playerTriesToStepToUp();
    bool playerTriesToStepToDown();

    std::default_random_engine random_engine;

    // Generators:
    DeliveryDirection getRandomDeliveryDirection();
    sf::Color getRandomDeliveryColor();
    float getRandomDeliverySpeed();
    ptrdiff_t getRandomDeliveryTarget();

  };
}
