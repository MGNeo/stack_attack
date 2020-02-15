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
      field.getCell(box.getSourceX(), box.getSourceY()).setOccupingBox(nullptr);

      box.fix();

      const size_t new_x = box.getSourceX();
      const size_t new_y = box.getSourceY() + 1u;

      if (field.isCellValid(new_x, new_y) == true)
      {
        if (field.getCell(new_x, new_y).getOccupyingBox() == nullptr)
        {
          box.stepToDown();
        }
      }

      field.getCell(box.getDestinationX(), box.getDestinationY()).setOccupingBox(&box);
    }
  }
}

void sa::LevelScene::controlPlayer()
{
  if (player.isReadyToStep() == true)
  {
    player.fix();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) == true)
    {
      if (playerTriesToStepToLeft() == true)
      {
        return;
      }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) == true)
    {
      if (playerTriesToStepToRight() == true)
      {
        return;
      }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) == true)
    {
      if (playerTriesToStepToUp() == true)
      {
        return;
      }
    }
    
    if (playerTriesToStepToDown() == true)
    {
      return;
    }

  }
  /*
  if (player.isReadyToStep() == true)
  {
    player.fix();
    
    const size_t x = player.getDestinationX();
    const size_t y = player.getDestinationY();

    // The processing step to left.
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
      bool playerStandsOntoSomething = false;
      if (field.isCellValid(x, y + 1u) == true)
      {
        if (field.getCell(x, y + 1u).getOccupyingBox() != nullptr)
        {
          playerStandsOntoSomething = true;
        }
      } else {
        playerStandsOntoSomething = true;
      }

      if ((field.isCellValid(x - 1u, y) == true) &&
          (field.isCellValid(x - 1u, y - 1u) == true) &&

          (field.getCell(x - 1u, y).getOccupyingBox() == nullptr) &&
          (field.getCell(x - 1u, y - 1u).getOccupyingBox() == nullptr))
      {
        if (playerStandsOntoSomething == true)
        {
          player.stepToLeft();
          return;
        } else {
          if (field.isCellValid(x - 1u, y + 1u) == true)
          {
            if (field.getCell(x - 1u, y + 1u).getOccupyingBox() != nullptr)
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
        if (field.getCell(x, y + 1u).getOccupyingBox() != nullptr)
        {
          playerStandsOntoSomething = true;
        }
      } else {
        playerStandsOntoSomething = true;
      }

      if ((field.isCellValid(x + 1u, y) == true) &&
          (field.isCellValid(x + 1u, y - 1u) == true) &&

          (field.getCell(x + 1u, y).getOccupyingBox() == nullptr) &&
          (field.getCell(x + 1u, y - 1u).getOccupyingBox() == nullptr))
      {
        if (playerStandsOntoSomething == true)
        {
          player.stepToRight();
          return;
        } else {
          if (field.isCellValid(x + 1u, y + 1u) == true)
          {
            if (field.getCell(x + 1u, y + 1u).getOccupyingBox() != nullptr)
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

          (field.getCell(x, y - 1u).getOccupyingBox() == nullptr) &&
          (field.getCell(x, y - 2u).getOccupyingBox() == nullptr))
      {
        if (field.isCellValid(x, y + 1u) == true)
        {
          if (field.getCell(x, y + 1u).getOccupyingBox() != nullptr)
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

        (field.getCell(x, y).getOccupyingBox() == nullptr) &&
        (field.getCell(x, y + 1u).getOccupyingBox() == nullptr))
    {
      player.stepToDown();
    }
  }
  */
}

bool sa::LevelScene::playerTriesToStepToLeft()
{
  const size_t x = player.getSourceX();
  const size_t y = player.getSourceY();

  bool player_stands_onto_something = false;

  if (field.isCellValid(x, y + 1u) == true)
  {
    if (field.getCell(x, y + 1u).getOccupyingBox() != nullptr)
    {
      player_stands_onto_something = true;
    }
  } else {
    player_stands_onto_something = true;
  }


  if ((field.isCellValid(x - 1u, y) == true) && (field.isCellValid(x - 1u, y - 1u) == true))
  {
    if (player_stands_onto_something == true)
    {
      if (field.getCell(x - 1u, y - 1u).getOccupyingBox() == nullptr)
      {
        if (field.getCell(x - 1u, y).getOccupyingBox() == nullptr)
        {
          player.stepToLeft();
          return true;
        } else {
          if (field.isCellValid(x - 2u, y) == true)
          {
            if (field.getCell(x - 2u, y).getOccupyingBox() == nullptr)
            {
              Box* const box = field.getCell(x - 1u, y).getOccupyingBox();
              if (box->isReadyToStep() == true)
              {
                box->stepToLeft();
                field.getCell(box->getDestinationX(), box->getDestinationY()).setOccupingBox(box);
                player.stepToLeft();
                return true;
              }
            }
          }
        }
      }
    } else {
      if (field.isCellValid(x - 1u, y + 1u) == true)// TODO: create relevant else branch.
      {
        if (field.getCell(x - 1u, y + 1u).getOccupyingBox() != nullptr)
        {
          if (field.getCell(x - 1u, y - 1u).getOccupyingBox() == nullptr)
          {
            if (field.getCell(x - 1u, y).getOccupyingBox() == nullptr)
            {
              player.stepToLeft();
              return true;
            } else {
              if (field.isCellValid(x - 2u, y) == true)
              {
                if (field.getCell(x - 2u, y).getOccupyingBox() == nullptr)
                {
                  Box* const box = field.getCell(x - 1u, y).getOccupyingBox();
                  if (box->isReadyToStep() == true)
                  {
                    box->stepToLeft();
                    field.getCell(box->getDestinationX(), box->getDestinationY()).setOccupingBox(box);
                    player.stepToLeft();
                    return true;
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  return false;
}

bool sa::LevelScene::playerTriesToStepToRight()
{

  const size_t x = player.getSourceX();
  const size_t y = player.getSourceY();

  bool player_stands_onto_something = false;

  if (field.isCellValid(x, y + 1u) == true)
  {
    if (field.getCell(x, y + 1u).getOccupyingBox() != nullptr)
    {
      player_stands_onto_something = true;
    }
  } else {
    player_stands_onto_something = true;
  }


  if ((field.isCellValid(x + 1u, y) == true) && (field.isCellValid(x + 1u, y - 1u) == true))
  {
    if (player_stands_onto_something == true)
    {
      if (field.getCell(x + 1u, y - 1u).getOccupyingBox() == nullptr)
      {
        if (field.getCell(x + 1u, y).getOccupyingBox() == nullptr)
        {
          player.stepToRight();
          return true;
        } else {
          if (field.isCellValid(x + 2u, y) == true)
          {
            if (field.getCell(x + 2u, y).getOccupyingBox() == nullptr)
            {
              Box* const box = field.getCell(x + 1u, y).getOccupyingBox();
              if (box->isReadyToStep() == true)
              {
                box->stepToRight();
                field.getCell(box->getDestinationX(), box->getDestinationY()).setOccupingBox(box);
                player.stepToRight();
                return true;
              }
            }
          }
        }
      }
    } else {
      if (field.isCellValid(x + 1u, y + 1u) == true)// TODO: Create relevant else branch.
      {
        if (field.getCell(x + 1u, y + 1u).getOccupyingBox() != nullptr)
        {
          if (field.getCell(x + 1u, y - 1u).getOccupyingBox() == nullptr)
          {
            if (field.getCell(x + 1u, y).getOccupyingBox() == nullptr)
            {
              player.stepToRight();
              return true;
            } else {
              if (field.isCellValid(x + 2u, y) == true)
              {
                if (field.getCell(x + 2u, y).getOccupyingBox() == nullptr)
                {
                  Box* const box = field.getCell(x + 1u, y).getOccupyingBox();
                  if (box->isReadyToStep() == true)
                  {
                    box->stepToRight();
                    field.getCell(box->getDestinationX(), box->getDestinationY()).setOccupingBox(box);
                    player.stepToRight();
                    return true;
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  return false;
}

bool sa::LevelScene::playerTriesToStepToUp()
{
  const size_t x = player.getSourceX();
  const size_t y = player.getSourceY();

  bool player_stands_onto_something = false;

  if (field.isCellValid(x, y + 1u) == true)
  {
    if (field.getCell(x, y + 1u).getOccupyingBox() != nullptr)
    {
      player_stands_onto_something = true;
    }
  } else {
    player_stands_onto_something = true;
  }

  if (player_stands_onto_something == true)
  {
    if ((field.isCellValid(x, y) == true) && (field.isCellValid(x, y - 1u) == true))
    {
      if ((field.getCell(x, y).getOccupyingBox() == nullptr) && (field.getCell(x, y - 1u).getOccupyingBox() == nullptr))
      {
        player.stepToUp();
        return true;
      }
    }
  }

  return false;
}

bool sa::LevelScene::playerTriesToStepToDown()
{
  const size_t x = player.getSourceX();
  const size_t y = player.getSourceY();

  if (field.isCellValid(x, y + 1u) == true)
  {
    if (field.getCell(x, y + 1u).getOccupyingBox() == nullptr)
    {
      player.stepToDown();
      return true;
    }
  }
  return false;
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
    sprite.setPosition(box.getRepresentedX() * 64.f, box.getRepresentedY() * 64.f);
    
    _drawer.draw(sprite);
  }

}

void sa::LevelScene::drawPlayer(const Drawer& _drawer) const
{
  sf::Texture texture = resource_library.getTexture("Unknown.bmp");

  sf::Sprite sprite;
  sprite.setTexture(texture, true);
  sprite.setScale(16, 16);

  sprite.setPosition(player.getRepresentedX() * 64.f, player.getRepresentedY() * 64.f);
  _drawer.draw(sprite);
  sprite.setPosition(player.getRepresentedX() * 64.f, (player.getRepresentedY() - 1) * 64.f);
  _drawer.draw(sprite);
}
