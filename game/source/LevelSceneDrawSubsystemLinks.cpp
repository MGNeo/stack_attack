#include <LevelSceneDrawSubsystemLinks.hpp>

sa::LevelSceneDrawSubsystemLinks::LevelSceneDrawSubsystemLinks(ResourceLibrary& _resource_library,
                                                               const Field& _field,
                                                               const Delivery::List& _deliveries,
                                                               const Box::List& _boxes,
                                                               const Player& _player)
  :
  resource_library{ _resource_library },
  field{ _field },
  deliveries{ _deliveries },
  boxes{ _boxes },
  player{ _player }
{
}

sa::ResourceLibrary& sa::LevelSceneDrawSubsystemLinks::getResourceLibrary() const
{
  return resource_library;
}

const sa::Field& sa::LevelSceneDrawSubsystemLinks::getField() const
{
  return field;
}
const sa::Delivery::List& sa::LevelSceneDrawSubsystemLinks::getDeliveries() const
{
  return deliveries;
}

const sa::Box::List& sa::LevelSceneDrawSubsystemLinks::getBoxes() const
{
  return boxes;
}

const sa::Player& sa::LevelSceneDrawSubsystemLinks::getPlayer() const
{
  return player;
}