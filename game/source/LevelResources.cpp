#include <LevelResources.hpp>

sa::LevelResources::LevelResources(ResourceLibrary& _resource_library)
{
  box = _resource_library.getTexture("Box.bmp");
}

const sf::Texture& sa::LevelResources::getBox() const
{
  return box;
}