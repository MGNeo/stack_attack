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
  // For debug.
  if (_event.type == sf::Event::EventType::KeyPressed)
  {
    Box box(0, 0);
    boxes.push_front(box);
  }
}

void sa::LevelScene::process(const float _dt)
{
  player.addProgress(_dt * 9);

  controlBoxes();
  processBoxes(_dt);
}

void sa::LevelScene::draw(const sa::Drawer& _drawer) const
{
  drawBoxes(_drawer);
}

sa::Scene::Uptr sa::LevelScene::getNextScene()
{
  return nullptr;
}

void sa::LevelScene::clearField()
{
  field.clear();
}

void sa::LevelScene::controlBoxes()
{
  for (auto& box : boxes)
  {
    if (box.isReadyToStep() == true)
    {
      const size_t new_y = box.getNextY() + 1u;

      // TODO: Optimise the logic.
      if (new_y >= field.getHeight())
      {
        field.getCell(box.getPreviousX(), box.getPreviousY()).setBusy(false);
        box.fix();
        field.getCell(box.getNextX(), box.getNextY()).setBusy(true);
      } else {
        if (field.getCell(box.getNextX(), new_y).getBusy() == true)
        {
          field.getCell(box.getPreviousX(), box.getPreviousY()).setBusy(false);
          box.fix();
          field.getCell(box.getNextX(), box.getNextY()).setBusy(true);
        } else {
          field.getCell(box.getPreviousX(), box.getPreviousY()).setBusy(false);
          box.stepToDown();
          field.getCell(box.getNextX(), box.getNextY()).setBusy(true);
        }
      }
    }
  }
}

void sa::LevelScene::processBoxes(const float _dt)
{
  for (auto& box : boxes)
  {
    box.addProgress(_dt);
  }
}

void sa::LevelScene::drawBoxes(const Drawer& _drawer) const
{
  sf::Texture texture = resource_library.getTexture("Box.bmp");

  sf::Sprite sprite;
  sprite.setTexture(texture, true);
  sprite.setOrigin(0.5f, 0.5f);

  //const float x_scale = 64.f / static_cast<float>(texture.getSize().x);
  //const float y_scale = 64.f / static_cast<float>(texture.getSize().y);

  //sprite.setScale(x_scale, y_scale);

  for (const auto& box : boxes)
  {
    sprite.setColor(box.getColor());
    sprite.setPosition(box.getX() * 64.f, box.getY() * 64.f);
    
    _drawer.draw(sprite);
  }
}