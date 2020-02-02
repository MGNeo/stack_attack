#include "Scene.hpp"

sa::Scene::Scene(sa::ResourceLibrary& _resource_library)
  :
  resource_library{ _resource_library }
{
}

bool sa::Scene::isActive() const
{
  return true;
}

sa::Scene::~Scene()
{
}