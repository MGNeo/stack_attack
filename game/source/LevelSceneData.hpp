#pragma once

#include <GameSettings.hpp>
#include <Field.hpp>
#include <Delivery.hpp>
#include <Box.hpp>
#include <Player.hpp>
#include <Shard.hpp>
#include <Profit.hpp>

namespace sa
{
  class LevelSceneData
  {
  public:

    LevelSceneData(const GameSettings& _game_settings);

    Field& accessToField();
    Delivery::List& accessToDeliveries();
    Box::List& accessToBoxes();
    Player& accessToPlayer();
    Shard::List& accessToShards();
    Profit::List& accessToProfits();

  private:

    Field field;
    Delivery::List deliveries;
    Box::List boxes;
    Player player;
    Shard::List shards;
    Profit::List profits;

  };
}
