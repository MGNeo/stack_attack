#pragma once

#include <LevelSceneData.hpp>
#include <GameSettings.hpp>
#include <random>

namespace sa
{
  class LevelSceneUpdateHandler
  {
  public:

    LevelSceneUpdateHandler(LevelSceneData& _data,
                             const GameSettings& _game_settings);

    void update(const float _dt);

  private:

    const sf::Color NON_MOVABLE_COLOR;

    LevelSceneData& data;
    const GameSettings& game_settings;

    std::default_random_engine random_engine;

    void updateDeliveries(const float _dt);
    void generateDelivery(const float _dt);
    void analyseTargetOfDelivery(Delivery& _delivery);
    void checkFinishOfDeliveries();

    void updateBoxes(const float _dt);
    void boxTriesToStepToDown(Box& _box);
    void analyseBottomLine();
    void analyseSectors();
    void deleteMarkedBoxes();

    void updatePlayer(const float _dt);
    bool playerTriesToStepToLeft();
    bool playerTriesToStepToRight();
    bool playerTriesToStepToUp();
    bool playerTriesToStepToDown();

    void updateShards(const float _dt);
    void deleteDisappearededShards();

    void updateProfits(const float _dt);
    void deleteDisappearedProfits();

    // Generators:
    void addRandomDelivery();
    void addBox(const sa::Delivery& _delivery);
    void addShards(const sa::Box& _box);
    void addProfit(const sa::Box& _box);

  };
}
