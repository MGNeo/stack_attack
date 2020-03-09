#include <LevelSceneData.hpp>

sa::LevelSceneData::LevelSceneData(const GameSettings& _game_settings)
  :
  field{ _game_settings.getFieldWidth(), _game_settings.getFieldHeight() },
  player{ _game_settings.getFieldWidth() / 2, _game_settings.getFieldHeight() - 1, _game_settings.getStepperSpeed() }
{
}

sa::Field& sa::LevelSceneData::accessToField()
{
  return field;
}

sa::Delivery::List& sa::LevelSceneData::accessToDeliveries()
{
  return deliveries;
}

sa::Box::List& sa::LevelSceneData::accessToBoxes()
{
  return boxes;
}

sa::Player& sa::LevelSceneData::accessToPlayer()
{
  return player;
}

sa::Shard::List& sa::LevelSceneData::accessToShards()
{
  return shards;
}

sa::Profit::List& sa::LevelSceneData::accessToProfits()
{
  return profits;
}