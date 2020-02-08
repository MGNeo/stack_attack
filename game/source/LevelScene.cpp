#include <LevelScene.hpp>

sa::LevelScene::LevelScene(sa::ResourceLibrary& _resource_library)
  :
  Scene{ _resource_library },
  level_resources{ resource_library }
{
}

void sa::LevelScene::control(const sf::Event& _event)
{

}

void sa::LevelScene::process(const float _dt)
{

}

void sa::LevelScene::draw(const sa::Drawer& _drawer) const
{
  
}

sa::Scene::Uptr sa::LevelScene::getNextScene()
{
  return nullptr;
}