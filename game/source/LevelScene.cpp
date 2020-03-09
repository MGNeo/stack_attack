#include <LevelScene.hpp>

sa::LevelScene::LevelScene(sa::ResourceLibrary& _resource_library,
                           const Drawer& _drawer,
                           const GameSettings& _game_settings)
  :
  Scene{ _resource_library, _drawer, _game_settings },
  data{ _game_settings },
  update_handler{ data, _game_settings },
  draw_handler{ _resource_library, _drawer, data, _game_settings }
{
}

void sa::LevelScene::react(const sf::Event& _event)
{
  // ...
}

void sa::LevelScene::update(const float _dt)
{
  update_handler.update(_dt);
}

void sa::LevelScene::draw() const
{
  draw_handler.draw();
}

sa::Scene::Uptr sa::LevelScene::getNextScene()
{
  return nullptr;
}
