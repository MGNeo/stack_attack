#include <LevelScene.hpp>

sa::LevelScene::LevelScene(sa::ResourceLibrary& _resource_library)
  :
  Scene{ _resource_library },
  NON_MOVABLE_COLOR{ 100u, 100u, 100u, 255u},
  field{ 12u, 9u },
  player{ 6u, 8u },
  random_engine{ clock() }
{
}

void sa::LevelScene::react(const sf::Event& _event)
{
  // For debug.
  if (_event.type == sf::Event::EventType::KeyPressed)
  {
    if (_event.key.code == sf::Keyboard::Space)
    {
      // ...
    }
  }
}

void sa::LevelScene::process(const float _dt)
{
  processDeliveries(_dt);
  processBoxes(_dt);
  processPlayer(_dt);
  processShards(_dt);
}

void sa::LevelScene::draw(const sa::Drawer& _drawer) const
{
  drawBoxes(_drawer);
  drawPlayer(_drawer);
  drawDeliveries(_drawer);
  drawShards(_drawer);
}

sa::Scene::Uptr sa::LevelScene::getNextScene()
{
  return nullptr;
}

void sa::LevelScene::drawDeliveries(const sa::Drawer& _drawer) const
{
  sf::Texture boxTexture = resource_library.getTexture("Box.png");
  sf::Texture deliveryTexture = resource_library.getTexture("Delivery.png");

  sf::Sprite boxSprite;
  boxSprite.setTexture(boxTexture, true);
  boxSprite.setScale(8.f, 8.f);

  sf::Sprite deliverySprite;
  deliverySprite.setTexture(deliveryTexture, true);
  deliverySprite.setScale(8.f, 8.f);

  const ptrdiff_t begin_cell = -1;
  const ptrdiff_t end_cell = field.getWidth();
  // Signed overflow is possible but it is impossible.
  const ptrdiff_t cell_difference = end_cell - begin_cell;

  for (const auto& delivery : deliveries)
  {
    const float represented_progress = delivery.getProgress();
    float represented_x{};

    switch (delivery.getDirection())
    {
      case (DeliveryDirection::FROM_LEFT_TO_RIGHT):
      {
        represented_x = begin_cell + represented_progress * cell_difference;
        break;
      }
      case (DeliveryDirection::FROM_RIGHT_TO_LEFT):
      {
        represented_x = end_cell - represented_progress * cell_difference;
        break;
      }
    }

    if (delivery.hasBox() == true)
    {
      boxSprite.setColor(delivery.getColor());
      boxSprite.setPosition(represented_x * 64.f, 0.f);
      _drawer.draw(boxSprite);
    }

    deliverySprite.setPosition(represented_x * 64.f, 0.f);
    _drawer.draw(deliverySprite);
  }
}

void sa::LevelScene::drawBoxes(const Drawer& _drawer) const
{
  sf::Texture texture = resource_library.getTexture("Box.png");

  sf::Sprite sprite;
  sprite.setTexture(texture, true);

  //const float x_scale = 64.f / static_cast<float>(texture.getSize().x);
  //const float y_scale = 64.f / static_cast<float>(texture.getSize().y);

  sprite.setScale(8.f, 8.f);

  for (const auto& box : boxes)
  {
    sprite.setColor(box.getColor());
    sprite.setPosition(box.getRepresentedX() * 64.f, box.getRepresentedY() * 64.f);

    _drawer.draw(sprite);
  }
}

void sa::LevelScene::drawPlayer(const Drawer& _drawer) const
{
  sf::Texture texture = resource_library.getTexture("Player.png");

  sf::Sprite sprite;
  sprite.setTexture(texture, true);
  sprite.setScale(8, 8);

  sprite.setPosition(player.getRepresentedX() * 64.f, (player.getRepresentedY() - 1) * 64.f);
  _drawer.draw(sprite);
}

void sa::LevelScene::processDeliveries(const float _dt)
{
  generateDelivery(_dt);
  for (auto& delivery : deliveries)
  {
    delivery.process(_dt);
    analyseTargetOfDelivery(delivery);
  }
  checkFinishOfDeliveries();
}

void sa::LevelScene::generateDelivery(const float _dt)
{
  static float timer;
  timer += _dt;

  if ((deliveries.size() < 5) && (timer >= 1.f))
  {
    timer = 0.f;

    deliveries.push_front(makeRandomDelivery());
  }
}

void sa::LevelScene::analyseTargetOfDelivery(Delivery& _delivery)
{
  if (_delivery.hasBox() == true)
  { 
    const float float_target = static_cast<float>(_delivery.getTarget());

    const ptrdiff_t begin_cell = -1;
    const ptrdiff_t end_cell = field.getWidth();
    // Signed overflow is possible but it is impossible.
    const ptrdiff_t cell_difference = end_cell - begin_cell;

    bool need_to_throw = false;

    switch (_delivery.getDirection())
    {
      case (DeliveryDirection::FROM_LEFT_TO_RIGHT):
      {
        const float float_position = static_cast<float>(begin_cell) + _delivery.getProgress() * cell_difference;
        if (float_position >= float_target)
        {
          need_to_throw = true;
        }
        break;
      }
      case (DeliveryDirection::FROM_RIGHT_TO_LEFT):
      {
        const float float_position = static_cast<float>(end_cell - _delivery.getProgress() * cell_difference);
        if (float_position <= float_target)
        {
          need_to_throw = true;
        }
        break;
      }
    }

    if (need_to_throw == true)
    {
      _delivery.throwBox();
      boxes.push_front({ _delivery.getTarget(), 0u, _delivery.getColor() });
    }
  }
}

void sa::LevelScene::checkFinishOfDeliveries()
{
  for (auto iterator = deliveries.begin(); iterator != deliveries.end();)
  {
    if (iterator->getProgress() == 1.f)
    {
      iterator = deliveries.erase(iterator);
    } else {
      ++iterator;
    }
  }
}

void sa::LevelScene::processBoxes(const float _dt)
{
  for (auto& box : boxes)
  {
    box.process(_dt*2);
    boxTriesToStepToDown(box);
  }
  analyseBottomLine();
  analyseSectors();
  deleteMarkedBoxes();
}

void sa::LevelScene::boxTriesToStepToDown(Box& _box)
{
  if (_box.isReadyToStep() == true)
  {
    field.getCell(_box.getSourceX(), _box.getSourceY()).setOccupingBox(nullptr);

    _box.fix();

    field.getCell(_box.getSourceX(), _box.getSourceY()).setOccupingBox(&_box);

    const size_t new_x = _box.getSourceX();
    const size_t new_y = static_cast<size_t>(_box.getSourceY()) + 1u;

    if (field.isCellValid(new_x, new_y) == true)
    {
      if (field.getCell(new_x, new_y).getOccupyingBox() == nullptr)
      {
        _box.stepToDown();
      }
    }
    field.getCell(_box.getDestinationX(), _box.getDestinationY()).setOccupingBox(&_box);
  }
}

void sa::LevelScene::analyseBottomLine()
{
  bool bottom_line_is_filled = true;

  const size_t y = field.getHeight() - 1u;

  for (size_t x = 0u; x < field.getWidth(); ++x)
  {
    const auto& cell = field.getCell(x, y);
    if ((cell.getOccupyingBox() == nullptr) || (cell.getOccupyingBox()->isReadyToStep() == false))
    {
      bottom_line_is_filled = false;
      break;
    }
  }

  if (bottom_line_is_filled == true)
  {
    std::list<Box*> marked_boxes;
    for (size_t x = 0u; x < field.getWidth(); ++x)
    {
      field.getCell(x, y).getOccupyingBox()->toMark();
    }
  }
}

void sa::LevelScene::analyseSectors()
{
  for (size_t x = 0u; x < field.getWidth(); ++x)
  {
    for (size_t y = 0u; y < field.getHeight(); ++y)
    {
      Box* const central_box = field.getCell(x, y).getOccupyingBox();
      if ((central_box != nullptr) && (central_box->isReadyToStep() == true))
      {
        std::list<Box*> selected_boxes;
        selected_boxes.push_front(central_box);

        auto analyse_cell = [&](const size_t _x, const size_t _y)
        {
          if (field.isCellValid(_x, _y) == true)
          {
            Box* const box = field.getCell(_x, _y).getOccupyingBox();
            if (box != nullptr)
            {
              if (box->isReadyToStep() == true)
              {
                if (box->getColor() == central_box->getColor())
                {
                  selected_boxes.push_back(box);
                }
              }
            }
          }
        };

        analyse_cell(x - 1u, y);
        analyse_cell(x + 1u, y);
        analyse_cell(x, y - 1u);
        analyse_cell(x, y + 1u);

        if (selected_boxes.size() >= 3u)
        {
          for (auto selected_box : selected_boxes)
          {
            selected_box->toMark();
          }
        }
      }
    }
  }
}

void sa::LevelScene::deleteMarkedBoxes()
{
  for (auto iterator = boxes.begin(); iterator != boxes.end();)
  {
    if (iterator->isMarked() == true)
    {
      for (size_t i = 0; i < 10; ++i)
      {
        shards.push_front(makeShard(*iterator));
      }

      field.getCell(iterator->getSourceX(), iterator->getSourceY()).setOccupingBox(nullptr);
      field.getCell(iterator->getDestinationX(), iterator->getDestinationY()).setOccupingBox(nullptr);
      iterator = boxes.erase(iterator);
    } else {
      ++iterator;
    }
  }
}

void sa::LevelScene::processPlayer(const float _dt)
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
  player.process(_dt*2);
}

bool sa::LevelScene::playerTriesToStepToLeft()
{
  const size_t x = player.getSourceX();
  const size_t y = player.getSourceY();

  bool player_stands_on_something_reliable = false;

  if (field.isCellValid(x, y + 1u) == true)
  {
    if (field.getCell(x, y + 1u).getOccupyingBox() != nullptr)
    {
      if (field.getCell(x, y + 1u).getOccupyingBox()->isReadyToStep() == true)
      {
        player_stands_on_something_reliable = true;
      }
    }
  } else {
    player_stands_on_something_reliable = true;
  }

  if ((field.isCellValid(x - 1u, y) == true) && (field.isCellValid(x - 1u, y - 1u) == true))
  {
    if (player_stands_on_something_reliable == true)
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
              if (box->getColor() != NON_MOVABLE_COLOR)
              {
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
    } else {
      if (field.isCellValid(x - 1u, y + 1u) == true)
      {
        if (field.getCell(x - 1u, y + 1u).getOccupyingBox() != nullptr)
        {
          if (field.getCell(x - 1u, y + 1u).getOccupyingBox()->isReadyToStep() == true)
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
                    if (box->getColor() != NON_MOVABLE_COLOR)
                    {
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
    }
  }
  return false;
}

bool sa::LevelScene::playerTriesToStepToRight()
{
  const size_t x = player.getSourceX();
  const size_t y = player.getSourceY();

  bool player_stands_on_something_reliable = false;

  if (field.isCellValid(x, y + 1u) == true)
  {
    if (field.getCell(x, y + 1u).getOccupyingBox() != nullptr)
    {
      if (field.getCell(x, y + 1u).getOccupyingBox()->isReadyToStep() == true)
      {
        player_stands_on_something_reliable = true;
      }
    }
  } else {
    player_stands_on_something_reliable = true;
  }

  if ((field.isCellValid(x + 1u, y) == true) && (field.isCellValid(x + 1u, y - 1u) == true))
  {
    if (player_stands_on_something_reliable == true)
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
              if (box->getColor() != NON_MOVABLE_COLOR)
              {
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
    } else {
      if (field.isCellValid(x + 1u, y + 1u) == true)
      {
        if (field.getCell(x + 1u, y + 1u).getOccupyingBox() != nullptr)
        {
          if (field.getCell(x + 1u, y + 1u).getOccupyingBox()->isReadyToStep() == true)
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
                    if (box->getColor() != NON_MOVABLE_COLOR)
                    {
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
    }
  }
  return false;
}

bool sa::LevelScene::playerTriesToStepToUp()
{
  const size_t x = player.getSourceX();
  const size_t y = player.getSourceY();

  bool player_stands_on_something_reliable = false;

  if (field.isCellValid(x, y + 1u) == true)
  {
    if (field.getCell(x, y + 1u).getOccupyingBox() != nullptr)
    {
      if (field.getCell(x, y + 1u).getOccupyingBox()->isReadyToStep() == true)
      {
        player_stands_on_something_reliable = true;
      }
    }
  } else {
    player_stands_on_something_reliable = true;
  }

  if (player_stands_on_something_reliable == true)
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

void sa::LevelScene::processShards(const float _dt)
{
  for (auto& shard : shards)
  {
    shard.setX(shard.getX() + shard.getVX() * _dt);
    shard.setY(shard.getY() + shard.getVY() * _dt);

    shard.reduceA(_dt);
  }
}

void sa::LevelScene::deleteFallenShards()
{
  for (auto iterator = shards.begin(); iterator != shards.end();)
  {
    // TODO.
    if (iterator->getColor().a == 0.f)
    {
      iterator = shards.erase(iterator);
    } else {
      ++iterator;
    }
  }
}

void sa::LevelScene::drawShards(const Drawer& _drawer) const
{
  sf::RectangleShape rectangle;

  for (auto& shard : shards)
  {
    rectangle.setSize({ 3.f, 3.f });

    sf::Color represented_color = shard.getColor();
    represented_color.a = static_cast<sf::Uint8>(shard.getA() * 255u);
    rectangle.setFillColor(represented_color);

    rectangle.setPosition(shard.getX() * 64.f, shard.getY() * 64.f);

    _drawer.draw(rectangle);
  }
}

sa::Delivery sa::LevelScene::makeRandomDelivery()
{
  DeliveryDirection direction{};
  {
    std::uniform_int_distribution uid{ 0u, 1u };
    switch (uid(random_engine))
    {
      case (0u):
      {
        direction = DeliveryDirection::FROM_LEFT_TO_RIGHT;
        break;
      }
      case (1u):
      {
        direction = DeliveryDirection::FROM_RIGHT_TO_LEFT;
        break;
      }
      default:
      {
        throw std::runtime_error("sa::LevelScene::makeRandomDelivery(), unknown value of DeliveryDirection was found.");
        break;
      }
    }
  }

  sf::Color color{};
  {
    const static sf::Color colors[] = { sf::Color::Red, sf::Color::Blue, sf::Color::Green, sf::Color::Yellow, NON_MOVABLE_COLOR };

    std::uniform_int_distribution uid{ 0u, std::size(colors) - 1u };
    color = colors[uid(random_engine)];
  }

  float speed{};
  {
    std::uniform_real_distribution urd{ 0.05f, 0.3f };
    speed = urd(random_engine);
  }

  ptrdiff_t target{};
  {
    std::uniform_int_distribution uid{ 0u, field.getWidth() - 1u };
    target = uid(random_engine);
  }

  return Delivery{ direction, speed, color, target };
}

sa::Shard sa::LevelScene::makeShard(const sa::Box& _box)
{
  std::uniform_real_distribution distribution_for_x{ 0.f, 1.f };
  std::uniform_real_distribution distribution_for_y{ 0.f, 1.f };
  const float x = _box.getRepresentedX() + distribution_for_x(random_engine);
  const float y = _box.getRepresentedY() + distribution_for_y(random_engine);

  std::uniform_real_distribution distribution_for_angle{ 0.f, 360.f };
  std::uniform_real_distribution distribution_for_speed{ 0.1f, 0.4f };
  const float angle = distribution_for_angle(random_engine);
  const float speed = distribution_for_speed(random_engine);
  const float vx = speed * cos(angle);
  const float vy = speed * sin(angle);

  const float a = 1.f;

  std::uniform_real_distribution distribution_for_av{ 0.3f, 1.f };
  const float av = distribution_for_av(random_engine);

  const sf::Color color = _box.getColor();

  return Shard(x, y, vx, vy, a, av, color);

}