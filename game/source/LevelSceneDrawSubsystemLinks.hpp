#pragma once

#include <ResourceLibrary.hpp>
#include <Field.hpp>
#include <Delivery.hpp>
#include <Box.hpp>
#include <Player.hpp>

namespace sa
{
  class LevelSceneDrawSubsystemLinks
  {

  public:

    LevelSceneDrawSubsystemLinks(ResourceLibrary& _resource_library,
                                 const Field& _field,
                                 const Delivery::List& _deliveries,
                                 const Box::List& _boxes,
                                 const Player& _player);

    ResourceLibrary& getResourceLibrary() const;
    const Field& getField() const;
    const Delivery::List& getDeliveries() const;
    const Box::List& getBoxes() const;
    const Player& getPlayer() const;

  private:
    
    ResourceLibrary& resource_library;
    const Field& field;
    const Delivery::List& deliveries;
    const Box::List& boxes;
    const Player& player;

  };
}
