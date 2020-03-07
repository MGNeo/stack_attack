#include <LevelSceneProcessHandler.hpp>

sa::LevelSceneProcessHandler::LevelSceneProcessHandler(sa::LevelSceneData& _data)
  :
  NON_MOVABLE_COLOR{ 155, 155, 155, 255 },
  data{ _data },
  random_engine{ clock() + static_cast<int>(time(NULL)) }
{
}

void sa::LevelSceneProcessHandler::process(const float _dt)
{
  processDeliveries(_dt);
  processBoxes(_dt);
  processPlayer(_dt);
  processShards(_dt);
}

void sa::LevelSceneProcessHandler::processDeliveries(const float _dt)
{
  generateDelivery(_dt);
  for (auto& delivery : data.accessToDeliveries())
  {
    delivery.process(_dt);
    analyseTargetOfDelivery(delivery);
  }
  checkFinishOfDeliveries();
}

void sa::LevelSceneProcessHandler::generateDelivery(const float _dt)
{
  static float timer;
  timer += _dt;

  if ((data.accessToDeliveries().size() < 5) && (timer >= 1.f))
  {
    timer = 0.f;

    data.accessToDeliveries().push_front(makeRandomDelivery());
  }
}

void sa::LevelSceneProcessHandler::analyseTargetOfDelivery(Delivery& _delivery)
{
  if (_delivery.hasBox() == true)
  {
    const float float_target = static_cast<float>(_delivery.getTarget());

    const ptrdiff_t begin_cell = -1;
    const ptrdiff_t end_cell = data.accessToField().getWidth();
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
      data.accessToBoxes().push_front({ _delivery.getTarget(), 0u, _delivery.getColor() });
    }
  }
}

void sa::LevelSceneProcessHandler::checkFinishOfDeliveries()
{
  for (auto iterator = data.accessToDeliveries().begin(); iterator != data.accessToDeliveries().end();)
  {
    if (iterator->getProgress() == 1.f)
    {
      iterator = data.accessToDeliveries().erase(iterator);
    } else {
      ++iterator;
    }
  }
}

void sa::LevelSceneProcessHandler::processBoxes(const float _dt)
{
  for (auto& box : data.accessToBoxes())
  {
    box.process(_dt * 2);
    boxTriesToStepToDown(box);
  }
  analyseBottomLine();
  analyseSectors();
  deleteMarkedBoxes();
}

void sa::LevelSceneProcessHandler::boxTriesToStepToDown(Box& _box)
{
  if (_box.isReadyToStep() == true)
  {
    data.accessToField().getCell(_box.getSourceX(), _box.getSourceY()).setOccupingBox(nullptr);

    _box.fix();

    data.accessToField().getCell(_box.getSourceX(), _box.getSourceY()).setOccupingBox(&_box);

    const size_t new_x = _box.getSourceX();
    const size_t new_y = static_cast<size_t>(_box.getSourceY()) + 1u;

    if (data.accessToField().isCellValid(new_x, new_y) == true)
    {
      if (data.accessToField().getCell(new_x, new_y).getOccupyingBox() == nullptr)
      {
        _box.stepToDown();
      }
    }
    data.accessToField().getCell(_box.getDestinationX(), _box.getDestinationY()).setOccupingBox(&_box);
  }
}

void sa::LevelSceneProcessHandler::analyseBottomLine()
{
  bool bottom_line_is_filled = true;

  const size_t y = data.accessToField().getHeight() - 1u;

  for (size_t x = 0u; x < data.accessToField().getWidth(); ++x)
  {
    const auto& cell = data.accessToField().getCell(x, y);
    if ((cell.getOccupyingBox() == nullptr) || (cell.getOccupyingBox()->isReadyToStep() == false))
    {
      bottom_line_is_filled = false;
      break;
    }
  }

  if (bottom_line_is_filled == true)
  {
    std::list<Box*> marked_boxes;
    for (size_t x = 0u; x < data.accessToField().getWidth(); ++x)
    {
      data.accessToField().getCell(x, y).getOccupyingBox()->toMark();
    }
  }
}

void sa::LevelSceneProcessHandler::analyseSectors()
{
  for (size_t x = 0u; x < data.accessToField().getWidth(); ++x)
  {
    for (size_t y = 0u; y < data.accessToField().getHeight(); ++y)
    {
      Box* const central_box = data.accessToField().getCell(x, y).getOccupyingBox();
      if ((central_box != nullptr) && (central_box->isReadyToStep() == true))
      {
        std::list<Box*> selected_boxes;
        selected_boxes.push_front(central_box);

        auto analyse_cell = [&](const size_t _x, const size_t _y)
        {
          if (data.accessToField().isCellValid(_x, _y) == true)
          {
            Box* const box = data.accessToField().getCell(_x, _y).getOccupyingBox();
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

void sa::LevelSceneProcessHandler::deleteMarkedBoxes()
{
  for (auto iterator = data.accessToBoxes().begin(); iterator != data.accessToBoxes().end();)
  {
    if (iterator->isMarked() == true)
    {
      for (size_t i = 0; i < 10; ++i)
      {
        data.accessToShards().push_front(makeShard(*iterator));
      }

      data.accessToField().getCell(iterator->getSourceX(), iterator->getSourceY()).setOccupingBox(nullptr);
      data.accessToField().getCell(iterator->getDestinationX(), iterator->getDestinationY()).setOccupingBox(nullptr);
      iterator = data.accessToBoxes().erase(iterator);
    } else {
      ++iterator;
    }
  }
}

void sa::LevelSceneProcessHandler::processPlayer(const float _dt)
{
  if (data.accessToPlayer().isReadyToStep() == true)
  {
    data.accessToPlayer().fix();

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
  data.accessToPlayer().process(_dt * 2);
}

bool sa::LevelSceneProcessHandler::playerTriesToStepToLeft()
{
  const size_t x = data.accessToPlayer().getSourceX();
  const size_t y = data.accessToPlayer().getSourceY();

  bool player_stands_on_something_reliable = false;

  if (data.accessToField().isCellValid(x, y + 1u) == true)
  {
    if (data.accessToField().getCell(x, y + 1u).getOccupyingBox() != nullptr)
    {
      if (data.accessToField().getCell(x, y + 1u).getOccupyingBox()->isReadyToStep() == true)
      {
        player_stands_on_something_reliable = true;
      }
    }
  } else {
    player_stands_on_something_reliable = true;
  }

  if ((data.accessToField().isCellValid(x - 1u, y) == true) && (data.accessToField().isCellValid(x - 1u, y - 1u) == true))
  {
    if (player_stands_on_something_reliable == true)
    {
      if (data.accessToField().getCell(x - 1u, y - 1u).getOccupyingBox() == nullptr)
      {
        if (data.accessToField().getCell(x - 1u, y).getOccupyingBox() == nullptr)
        {
          data.accessToPlayer().stepToLeft();
          return true;
        } else {
          if (data.accessToField().isCellValid(x - 2u, y) == true)
          {
            if (data.accessToField().getCell(x - 2u, y).getOccupyingBox() == nullptr)
            {
              Box* const box = data.accessToField().getCell(x - 1u, y).getOccupyingBox();
              if (box->getColor() != NON_MOVABLE_COLOR)
              {
                if (box->isReadyToStep() == true)
                {
                  box->stepToLeft();
                  data.accessToField().getCell(box->getDestinationX(), box->getDestinationY()).setOccupingBox(box);
                  data.accessToPlayer().stepToLeft();
                  return true;
                }
              }
            }
          }
        }
      }
    } else {
      if (data.accessToField().isCellValid(x - 1u, y + 1u) == true)
      {
        if (data.accessToField().getCell(x - 1u, y + 1u).getOccupyingBox() != nullptr)
        {
          if (data.accessToField().getCell(x - 1u, y + 1u).getOccupyingBox()->isReadyToStep() == true)
          {
            if (data.accessToField().getCell(x - 1u, y - 1u).getOccupyingBox() == nullptr)
            {
              if (data.accessToField().getCell(x - 1u, y).getOccupyingBox() == nullptr)
              {
                data.accessToPlayer().stepToLeft();
                return true;
              } else {
                if (data.accessToField().isCellValid(x - 2u, y) == true)
                {
                  if (data.accessToField().getCell(x - 2u, y).getOccupyingBox() == nullptr)
                  {
                    Box* const box = data.accessToField().getCell(x - 1u, y).getOccupyingBox();
                    if (box->getColor() != NON_MOVABLE_COLOR)
                    {
                      if (box->isReadyToStep() == true)
                      {
                        box->stepToLeft();
                        data.accessToField().getCell(box->getDestinationX(), box->getDestinationY()).setOccupingBox(box);
                        data.accessToPlayer().stepToLeft();
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

bool sa::LevelSceneProcessHandler::playerTriesToStepToRight()
{
  const size_t x = data.accessToPlayer().getSourceX();
  const size_t y = data.accessToPlayer().getSourceY();

  bool player_stands_on_something_reliable = false;

  if (data.accessToField().isCellValid(x, y + 1u) == true)
  {
    if (data.accessToField().getCell(x, y + 1u).getOccupyingBox() != nullptr)
    {
      if (data.accessToField().getCell(x, y + 1u).getOccupyingBox()->isReadyToStep() == true)
      {
        player_stands_on_something_reliable = true;
      }
    }
  } else {
    player_stands_on_something_reliable = true;
  }

  if ((data.accessToField().isCellValid(x + 1u, y) == true) && (data.accessToField().isCellValid(x + 1u, y - 1u) == true))
  {
    if (player_stands_on_something_reliable == true)
    {
      if (data.accessToField().getCell(x + 1u, y - 1u).getOccupyingBox() == nullptr)
      {
        if (data.accessToField().getCell(x + 1u, y).getOccupyingBox() == nullptr)
        {
          data.accessToPlayer().stepToRight();
          return true;
        } else {
          if (data.accessToField().isCellValid(x + 2u, y) == true)
          {
            if (data.accessToField().getCell(x + 2u, y).getOccupyingBox() == nullptr)
            {
              Box* const box = data.accessToField().getCell(x + 1u, y).getOccupyingBox();
              if (box->getColor() != NON_MOVABLE_COLOR)
              {
                if (box->isReadyToStep() == true)
                {
                  box->stepToRight();
                  data.accessToField().getCell(box->getDestinationX(), box->getDestinationY()).setOccupingBox(box);
                  data.accessToPlayer().stepToRight();
                  return true;
                }
              }
            }
          }
        }
      }
    } else {
      if (data.accessToField().isCellValid(x + 1u, y + 1u) == true)
      {
        if (data.accessToField().getCell(x + 1u, y + 1u).getOccupyingBox() != nullptr)
        {
          if (data.accessToField().getCell(x + 1u, y + 1u).getOccupyingBox()->isReadyToStep() == true)
          {
            if (data.accessToField().getCell(x + 1u, y - 1u).getOccupyingBox() == nullptr)
            {
              if (data.accessToField().getCell(x + 1u, y).getOccupyingBox() == nullptr)
              {
                data.accessToPlayer().stepToRight();
                return true;
              } else {
                if (data.accessToField().isCellValid(x + 2u, y) == true)
                {
                  if (data.accessToField().getCell(x + 2u, y).getOccupyingBox() == nullptr)
                  {
                    Box* const box = data.accessToField().getCell(x + 1u, y).getOccupyingBox();
                    if (box->getColor() != NON_MOVABLE_COLOR)
                    {
                      if (box->isReadyToStep() == true)
                      {
                        box->stepToRight();
                        data.accessToField().getCell(box->getDestinationX(), box->getDestinationY()).setOccupingBox(box);
                        data.accessToPlayer().stepToRight();
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

bool sa::LevelSceneProcessHandler::playerTriesToStepToUp()
{
  const size_t x = data.accessToPlayer().getSourceX();
  const size_t y = data.accessToPlayer().getSourceY();

  bool player_stands_on_something_reliable = false;

  if (data.accessToField().isCellValid(x, y + 1u) == true)
  {
    if (data.accessToField().getCell(x, y + 1u).getOccupyingBox() != nullptr)
    {
      if (data.accessToField().getCell(x, y + 1u).getOccupyingBox()->isReadyToStep() == true)
      {
        player_stands_on_something_reliable = true;
      }
    }
  } else {
    player_stands_on_something_reliable = true;
  }

  if (player_stands_on_something_reliable == true)
  {
    if ((data.accessToField().isCellValid(x, y) == true) && (data.accessToField().isCellValid(x, y - 1u) == true))
    {
      if ((data.accessToField().getCell(x, y).getOccupyingBox() == nullptr) && (data.accessToField().getCell(x, y - 1u).getOccupyingBox() == nullptr))
      {
        data.accessToPlayer().stepToUp();
        return true;
      }
    }
  }

  return false;
}

bool sa::LevelSceneProcessHandler::playerTriesToStepToDown()
{
  const size_t x = data.accessToPlayer().getSourceX();
  const size_t y = data.accessToPlayer().getSourceY();

  if (data.accessToField().isCellValid(x, y + 1u) == true)
  {
    if (data.accessToField().getCell(x, y + 1u).getOccupyingBox() == nullptr)
    {
      data.accessToPlayer().stepToDown();
      return true;
    }
  }
  return false;
}

void sa::LevelSceneProcessHandler::processShards(const float _dt)
{
  for (auto& shard : data.accessToShards())
  {
    shard.setX(shard.getX() + shard.getVX() * _dt);
    shard.setY(shard.getY() + shard.getVY() * _dt);

    shard.reduceA(_dt);
  }
}

void sa::LevelSceneProcessHandler::deleteDisappearededShards()
{
  for (auto iterator = data.accessToShards().begin(); iterator != data.accessToShards().end();)
  {
    // TODO.
    if (iterator->getColor().a == 0.f)
    {
      iterator = data.accessToShards().erase(iterator);
    } else {
      ++iterator;
    }
  }
}

// Generators:
sa::Delivery sa::LevelSceneProcessHandler::makeRandomDelivery()
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
        throw std::runtime_error("sa::LevelSceneProcessHandler::makeRandomDelivery(), unknown value of DeliveryDirection was found.");
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
    std::uniform_int_distribution uid{ 0u, data.accessToField().getWidth() - 1u };
    target = uid(random_engine);
  }

  return Delivery{ direction, speed, color, target };
}

sa::Shard sa::LevelSceneProcessHandler::makeShard(const sa::Box& _box)
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
