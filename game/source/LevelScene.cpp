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
    if (player.getStepper().isReady())
    {
      switch (_event.key.code)
      {
        case (sf::Keyboard::Left):
        {
          player.getStepper().toLeft();
          break;
        }
        case (sf::Keyboard::Right):
        {
          player.getStepper().toRight();
          break;
        }
        case (sf::Keyboard::Up):
        {
          player.getStepper().toUp();
          break;
        }
        case (sf::Keyboard::Down):
        {
          player.getStepper().toDown();
          break;
        }
      }
    }
  }
}

void sa::LevelScene::process(const float _dt)
{
  player.getStepper().addProgress(_dt);
}

void sa::LevelScene::draw(const sa::Drawer& _drawer) const
{
  player.draw(_drawer);
}

sa::Scene::Uptr sa::LevelScene::getNextScene()
{
  return nullptr;
}