#include "ResourceLibrary.hpp"

const std::string sa::ResourceLibrary::TEXTURE_PATH = "textures/";
const std::string sa::ResourceLibrary::DEFAULT_TEXTURE_NAME = "Default.bmp";

sa::ResourceLibrary::ResourceLibrary()
{
  //sf::RenderWindow render_window(sf::VideoMode(640, 480), "123");
  sf::Texture texture;
  if (texture.loadFromFile(TEXTURE_PATH + DEFAULT_TEXTURE_NAME) == true)
  {
    textures.insert({DEFAULT_TEXTURE_NAME, texture});
  } else {
    throw std::runtime_error("sa::ResourceLibrary::ResourceLibrary(), default texture can't be loaded.");
  }
}


sf::Texture& sa::ResourceLibrary::getTexture(const std::string& _name)
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

/*
sf::Font& sa::ResourceLibrary::getFont(const std::string& _name)
{
  sf::Font font;
  // ...
  return font;
}
*/