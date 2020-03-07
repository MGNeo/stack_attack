#include <LevelSceneData.hpp>

// TODO: Perhaps, we need special settings for constructing of LevelSceneData.
sa::LevelSceneData::LevelSceneData(ResourceLibrary& _resource_library,
                                   const size_t _field_width,
                                   const size_t _field_height)
  :
  resource_library{ _resource_library },
  field{ _field_width, _field_height },
  player{ _field_width / 2, _field_height - 1u }
{
}

sa::ResourceLibrary& sa::LevelSceneData::accessToResourceLibrary()
{
  return resource_library;
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