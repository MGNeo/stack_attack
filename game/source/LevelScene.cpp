#include <LevelScene.hpp>

sa::LevelScene::LevelScene(sa::ResourceLibrary& _resource_library)
  :
  Scene{ _resource_library },
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
  player.addProgress(_dt * 9);
}

void sa::LevelScene::draw(const sa::Drawer& _drawer) const
{
  sf::Sprite sprite;
  sprite.setTexture(resource_library.getTexture("Box.bmp"));
  sprite.setPosition(200, 200);
  sprite.setColor({ 255, 255, 0, 255 });
  _drawer.draw(sprite);
}

sa::Scene::Uptr sa::LevelScene::getNextScene()
{
  return nullptr;
}