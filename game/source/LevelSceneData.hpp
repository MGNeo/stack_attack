#pragma once

#include <ResourceLibrary.hpp>
#include <Field.hpp>
#include <Delivery.hpp>
#include <Box.hpp>
#include <Player.hpp>
#include <Shard.hpp>

namespace sa
{
  class LevelSceneData
  {
  public:

    LevelSceneData(ResourceLibrary& _resource_library,
                   const size_t _field_width,
                   const size_t _field_height);

    ResourceLibrary& accessToResourceLibrary();
    Field& accessToField();
    Delivery::List& accessToDeliveries();
    Box::List& accessToBoxes();
    Player& accessToPlayer();
    Shard::List& accessToShards();

  private:

    ResourceLibrary& resource_library;
    Field field;
    Delivery::List deliveries;
    Box::List boxes;
    Player player;
    Shard::List shards;

  };
}
