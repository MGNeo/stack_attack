#include <Scene.hpp>

sa::Scene::Scene(ResourceLibrary& _resource_library,
                 const Drawer& _drawer,
                 const GameSettings& _game_settings)
  :
  resource_library{ _resource_library },
  drawer{ _drawer },
  game_settings{ _game_settings }
{
}

bool sa::Scene::isActive() const
{
  return true;
}

sa::Scene::~Scene()
{
}