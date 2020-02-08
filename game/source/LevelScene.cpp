#include <LevelScene.hpp>

sa::LevelScene::LevelScene(sa::ResourceLibrary& _resource_library)
  :
  Scene{ _resource_library },
  level_resources{ resource_library },
  field{ 13u, 10u },
  player{ 5, 5 }
{
}

void sa::LevelScene::control(const sf::Event& _event)
{
  if (_event.type == sf::Event::EventType::KeyPressed)
  {
    if (player.isReadyToStep())
    {
      switch (_event.key.code)
      {
        case (sf::Keyboard::Left):
        {
          player.stepToLeft();
          break;
        }
        case (sf::Keyboard::Right):
        {
          player.stepToRight();
          break;
        }
        case (sf::Keyboard::Up):
        {
          player.stepToUp();
          break;
        }
        case (sf::Keyboard::Down):
        {
          player.stepToDown();
          break;
        }
      }
    }
  }
}

void sa::LevelScene::process(const float _dt)
{
  player.progress(_dt*9);
}

void sa::LevelScene::draw(const sa::Drawer& _drawer) const
{
  player.draw(_drawer);
}

sa::Scene::Uptr sa::LevelScene::getNextScene()
{
  return nullptr;
}