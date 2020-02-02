#include <SFML/Graphics.hpp>

#include "Game.hpp"
#include "LevelScene.hpp"

sa::Game::Game()
  :
  render_window(sf::VideoMode(800u, 600u), "stack_attack")
{
}

void sa::Game::play()
{
  sa::Scene::Uptr scene = std::make_unique<sa::LevelScene>(render_window, resource_library);

  while (scene != nullptr)
  {
    scene = scene->run();
  }
}