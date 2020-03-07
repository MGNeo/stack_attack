#include <LevelScene.hpp>

sa::LevelScene::LevelScene(sa::ResourceLibrary& _resource_library)
  :
  data{ _resource_library, 13, 9},
  process_handler{ data },
  draw_handler{ data }
{
}

void sa::LevelScene::react(const sf::Event& _event)
{
  // ...
}

void sa::LevelScene::process(const float _dt)
{
  process_handler.process(_dt);
}

void sa::LevelScene::draw(const sa::Drawer& _drawer) const
{
  draw_handler.draw(_drawer);
}

sa::Scene::Uptr sa::LevelScene::getNextScene()
{
  return nullptr;
}
