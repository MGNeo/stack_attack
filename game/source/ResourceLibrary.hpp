#pragma once

#include <SFML/Graphics.hpp>

#include <map>
#include <string>

namespace sa
{
  class ResourceLibrary
  {
  public:
    ResourceLibrary();
    sf::Texture& getTexture(const std::string& _name);
  private:
    std::map<std::string, sf::Texture> textures;

    const std::string TEXTURE_PATH;
    const std::string DEFAULT_TEXTURE_NAME;
  };
}

