#include <LevelScene.hpp>

sa::LevelScene::LevelScene(sa::ResourceLibrary& _resource_library)
  :
  Scene{ _resource_library },
  field{ 13u, 9u },
  player{ 5u, 5u }
{
}

void sa::LevelScene::react(const sf::Event& _event)
{
  // For debug.
  if (_event.type == sf::Event::EventType::KeyPressed)
  {
    if (_event.key.code == sf::Keyboard::Space)
    {
      sf::Color color;
      switch (rand() % 4)
      {
        case (0):
        {
          color = sf::Color::Red;
          break;
        }
        case (1):
        {
          color = sf::Color::Blue;
          break;
        }
        case (2):
        {
          color = sf::Color::Yellow;
          break;
        }
        case (3):
        {
          color = sf::Color::Green;
          break;
        }
      }
      Box box(rand() % 13, 0, color);
      boxes.push_front(box);
    }
  }
}

void sa::LevelScene::process(const float _dt)
{
  controlBoxes();
  controlPlayer();
  processBoxes(_dt);
  processPlayer(_dt);
}

void sa::LevelScene::draw(const sa::Drawer& _drawer) const
{
  drawBoxes(_drawer);
  drawPlayer(_drawer);
}

sa::Scene::Uptr sa::LevelScene::getNextScene()
{
  return nullptr;
}

void sa::LevelScene::controlBoxes()
{
  for (auto& box : boxes)
  {
    if (box.isReadyToStep() == true)
    {
      const size_t new_y = box.getNextY() + 1u;

      auto& previous_cell = field.getCell(box.getPreviousX(), box.getPreviousY());

      // TODO: Optimise the logic.
      if (new_y >= field.getHeight())
      {
        previous_cell.setBusy(false);
        box.fix();
        field.getCell(box.getNextX(), box.getNextY()).setBusy(true);
      } else {
        if (field.getCell(box.getNextX(), new_y).getBusy() == true)
        {
          previous_cell.setBusy(false);
          box.fix();
          field.getCell(box.getNextX(), box.getNextY()).setBusy(true);
        } else {
          previous_cell.setBusy(false);
          box.stepToDown();
          field.getCell(box.getNextX(), box.getNextY()).setBusy(true);
        }
      }
    }
  }
}

void sa::LevelScene::controlPlayer()
{
  if (player.isReadyToStep() == true)
  {
    player.fix();
    
    const size_t x = player.getNextX();
    const size_t y = player.getNextY();

    // The processing step to left.
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
      bool playerStandsOntoSomething = false;
      if (field.isCellValid(x, y + 1u) == true)
      {
        if (field.getCell(x, y + 1u).getBusy() == true)
        {
          playerStandsOntoSomething = true;
        }
      } else {
        playerStandsOntoSomething = true;
      }

      if ((field.isCellValid(x - 1u, y) == true) &&
          (field.isCellValid(x - 1u, y - 1u) == true) &&

          (field.getCell(x - 1u, y).getBusy() == false) &&
          (field.getCell(x - 1u, y - 1u).getBusy() == false))
      {
        if (playerStandsOntoSomething == true)
        {
          player.stepToLeft();
          return;
        } else {
          if (field.isCellValid(x - 1u, y + 1u) == true)
          {
            if (field.getCell(x - 1u, y + 1u).getBusy() == true)
            {
              player.stepToLeft();
              return;
            }
          } else {
            player.stepToLeft();
            return;
          }
        }
      }
    }

    // The processing step to right.
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
      bool playerStandsOntoSomething = false;
      if (field.isCellValid(x, y + 1u) == true)
      {
        if (field.getCell(x, y + 1u).getBusy() == true)
        {
          playerStandsOntoSomething = true;
        }
      } else {
        playerStandsOntoSomething = true;
      }

      if ((field.isCellValid(x + 1u, y) == true) &&
          (field.isCellValid(x + 1u, y - 1u) == true) &&

          (field.getCell(x + 1u, y).getBusy() == false) &&
          (field.getCell(x + 1u, y - 1u).getBusy() == false))
      {
        if (playerStandsOntoSomething == true)
        {
          player.stepToRight();
          return;
        } else {
          if (field.isCellValid(x + 1u, y + 1u) == true)
          {
            if (field.getCell(x + 1u, y + 1u).getBusy() == true)
            {
              player.stepToRight();
              return;
            }
          } else {
            player.stepToRight();
            return;
          }
        }
      }
    }

    // The processing step to up.
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
      if ((field.isCellValid(x, y - 1u) == true) &&
          (field.isCellValid(x, y - 2u) == true) &&

          (field.getCell(x, y - 1u).getBusy() == false) &&
          (field.getCell(x, y - 2u).getBusy() == false))
      {
        if (field.isCellValid(x, y + 1u) == true)
        {
          if (field.getCell(x, y + 1u).getBusy() == true)
          {
            player.stepToUp();
            return;
          }
        } else {
          player.stepToUp();
          return;
        }
      }
    }

    // TODO: Process step from box to void.
    
    // The processing gravity.
    if ((field.isCellValid(x, y) == true) &&
        (field.isCellValid(x, y + 1u) == true) &&
        
        (field.getCell(x, y).getBusy() == false) &&
        (field.getCell(x, y + 1u).getBusy() == false))
    {
      player.stepToDown();
    }
  }
}

void sa::LevelScene::processBoxes(const float _dt)
{
  for (auto& box : boxes)
  {
    box.process(_dt*2);
  }
}

void sa::LevelScene::processPlayer(const float _dt)
{
  player.process(_dt*2);
}

void sa::LevelScene::drawBoxes(const Drawer& _drawer) const
{
  sf::Texture texture = resource_library.getTexture("Box.bmp");

  sf::Sprite sprite;
  sprite.setTexture(texture, true);

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

void sa::LevelScene::drawPlayer(const Drawer& _drawer) const
{
  sf::Texture texture = resource_library.getTexture("Unknown.bmp");

  sf::Sprite sprite;
  sprite.setTexture(texture, true);
  sprite.setScale(16, 16);

  sprite.setPosition(player.getX() * 64.f, player.getY() * 64.f);
  _drawer.draw(sprite);
  sprite.setPosition(player.getX() * 64.f, (player.getY() - 1) * 64.f);
  _drawer.draw(sprite);
}
