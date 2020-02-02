#include "Scene.hpp"

sa::Scene::Scene(sa::ResourceLibrary& _resource_library)
  :
  active { true },
  resource_library{ _resource_library }
{
}

bool sa::Scene::isActive() const
{
  return active;
}

void sa::Scene::disable()
{
  active = false;
}

sa::Scene::~Scene()
{
}