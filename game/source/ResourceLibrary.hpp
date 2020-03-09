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
    
    const sf::Texture& getTexture(const std::string& _name);
    const sf::Font& getFont(const std::string& _name);

  private:

    std::map<std::string, sf::Texture> textures;
    std::map<std::string, sf::Font> fonts;

    const std::string TEXTURE_PATH;
    const std::string DEFAULT_TEXTURE_NAME;

    const std::string FONT_PATH;
    const std::string DEFAULT_FONT_NAME;
  };
}

