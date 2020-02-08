#pragma once

#include <SFML/Graphics.hpp>
#include <ResourceLibrary.hpp>

namespace sa
{

  class LevelResources
  {
  public:

    LevelResources(ResourceLibrary& _resource_library);

    const sf::Texture& getBox() const;

  private:
    
    sf::Texture box;

  };
}
