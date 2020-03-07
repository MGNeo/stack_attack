#pragma once

#include <LevelSceneData.hpp>
#include <GameSettings.hpp>
#include <random>

namespace sa
{
  class LevelSceneProcessHandler
  {
  public:

    LevelSceneProcessHandler(LevelSceneData& _data,
                             const GameSettings& _game_settings);

    void process(const float _dt);

  private:

    const sf::Color NON_MOVABLE_COLOR;

    LevelSceneData& data;
    const GameSettings& game_settings;

    std::default_random_engine random_engine;

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

    void processShards(const float _dt);
    void deleteDisappearededShards();

    Delivery makeRandomDelivery();
    Shard makeShard(const sa::Box& _box);
  };
}
