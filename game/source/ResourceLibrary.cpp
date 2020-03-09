#include <ResourceLibrary.hpp>

sa::ResourceLibrary::ResourceLibrary()
  :
  TEXTURE_PATH{"textures/"},
  DEFAULT_TEXTURE_NAME{ "Default.bmp" },
  FONT_PATH{"fonts/"},
  DEFAULT_FONT_NAME{"Default.ttf"}
{
  sf::Texture texture;
  if (texture.loadFromFile(TEXTURE_PATH + DEFAULT_TEXTURE_NAME) == true)
  {
    textures.insert({DEFAULT_TEXTURE_NAME, texture});
  } else {
    throw std::runtime_error("sa::ResourceLibrary::ResourceLibrary(), default texture can't be loaded.");
  }

  sf::Font font;
  if (font.loadFromFile(FONT_PATH + DEFAULT_FONT_NAME) == true)
  {
    fonts.insert({DEFAULT_FONT_NAME, font});
  } else {
    throw std::runtime_error("sa::ResourceLibrary::ResourceLibrary(), default font can't be loaded.");
  }
}


const sf::Texture& sa::ResourceLibrary::getTexture(const std::string& _name)
{
  const auto iterator = textures.find(_name);

  if (iterator != textures.end())
  {
    return iterator->second;
  }
  else
  {
    sf::Texture texture;
    if (texture.loadFromFile(TEXTURE_PATH + _name) == true)
    {
      const auto result = textures.insert({ _name, texture });
      if (result.second == true)
      {
        return result.first->second;
      } else {
        throw std::runtime_error("sa::ResourceLibrary::getTexture(), texture can't be inserted.");
      }
    } else {
      return textures[DEFAULT_TEXTURE_NAME];
    }
  }
}


const sf::Font& sa::ResourceLibrary::getFont(const std::string& _name)
{
  const auto iterator = fonts.find(_name);

  if (iterator != fonts.end())
  {
    return iterator->second;
  } else {
    sf::Font font;
    if (font.loadFromFile(FONT_PATH + _name) == true)
    {
      const auto result = fonts.insert({_name, font});
      if (result.second == true)
      {
        return result.first->second;
      } else {
        throw std::runtime_error("sa::ResourceLibrary::getFont(), font cen't be inserted.");
      }
    } else {
      return fonts[DEFAULT_FONT_NAME];
    }
  }
}
