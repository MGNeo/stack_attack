#include <LevelSceneUpdateHandler.hpp>

sa::LevelSceneUpdateHandler::LevelSceneUpdateHandler(LevelSceneData& _data,
                                                     const GameSettings& _game_settings)
  :
  NON_MOVABLE_COLOR{ 155, 155, 155, 255 },
  data{ _data },
  game_settings{ _game_settings },
  random_engine{ clock() + static_cast<int>(time(NULL)) }
{
}

void sa::LevelSceneUpdateHandler::update(const float _dt)
{
  updateDeliveries(_dt);
  updateBoxes(_dt);
  updatePlayer(_dt);
  updateShards(_dt);
  updateProfits(_dt);
}

void sa::LevelSceneUpdateHandler::updateDeliveries(const float _dt)
{
  generateDelivery(_dt);
  for (auto& delivery : data.accessToDeliveries())
  {
    delivery.update(_dt);
    analyseTargetOfDelivery(delivery);
  }
  checkFinishOfDeliveries();
}

void sa::LevelSceneUpdateHandler::generateDelivery(const float _dt)
{
  static float timer;
  timer += _dt;

  // TODO: Take this info from game_settings.
  if ((data.accessToDeliveries().size() < 5) && (timer >= 1.f))
  {
    timer = 0.f;

    addRandomDelivery();
  }
}

void sa::LevelSceneUpdateHandler::analyseTargetOfDelivery(Delivery& _delivery)
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
      addBox(_delivery);
    }
  }
}

void sa::LevelSceneUpdateHandler::checkFinishOfDeliveries()
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

void sa::LevelSceneUpdateHandler::updateBoxes(const float _dt)
{
  for (auto& box : data.accessToBoxes())
  {
    box.updateProgress(_dt);
    boxTriesToStepToDown(box);
  }
  analyseBottomLine();
  analyseSectors();
  deleteMarkedBoxes();
}

void sa::LevelSceneUpdateHandler::boxTriesToStepToDown(Box& _box)
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

void sa::LevelSceneUpdateHandler::analyseBottomLine()
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

void sa::LevelSceneUpdateHandler::analyseSectors()
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

void sa::LevelSceneUpdateHandler::deleteMarkedBoxes()
{
  for (auto iterator = data.accessToBoxes().begin(); iterator != data.accessToBoxes().end();)
  {
    if (iterator->isMarked() == true)
    {
      addShards(*iterator);
      addProfit(*iterator);

      data.accessToField().getCell(iterator->getSourceX(), iterator->getSourceY()).setOccupingBox(nullptr);
      data.accessToField().getCell(iterator->getDestinationX(), iterator->getDestinationY()).setOccupingBox(nullptr);
      iterator = data.accessToBoxes().erase(iterator);
    } else {
      ++iterator;
    }
  }
}

void sa::LevelSceneUpdateHandler::updatePlayer(const float _dt)
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
  data.accessToPlayer().updateProgress(_dt);
}

bool sa::LevelSceneUpdateHandler::playerTriesToStepToLeft()
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

bool sa::LevelSceneUpdateHandler::playerTriesToStepToRight()
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

bool sa::LevelSceneUpdateHandler::playerTriesToStepToUp()
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

bool sa::LevelSceneUpdateHandler::playerTriesToStepToDown()
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

void sa::LevelSceneUpdateHandler::updateShards(const float _dt)
{
  for (auto& shard : data.accessToShards())
  {
    shard.updatePosition(_dt);
    shard.updateAlpha(_dt);
  }
}

void sa::LevelSceneUpdateHandler::deleteDisappearededShards()
{
  for (auto iterator = data.accessToShards().begin(); iterator != data.accessToShards().end();)
  {
    // TODO.
    if (iterator->getA() == 0.f)
    {
      iterator = data.accessToShards().erase(iterator);
    } else {
      ++iterator;
    }
  }
}

void sa::LevelSceneUpdateHandler::updateProfits(const float _dt)
{
  for (auto& profit : data.accessToProfits())
  {
    profit.updateAlpha(_dt);
  }
}

void sa::LevelSceneUpdateHandler::deleteDisappearedProfits()
{
  for (auto iterator = data.accessToProfits().begin(); iterator != data.accessToProfits().end();)
  {
    // TODO.
    if (iterator->getA() == 0.f)
    {
      iterator = data.accessToProfits().erase(iterator);
    } else {
      ++iterator;
    }
  }
}

// Generators:
void sa::LevelSceneUpdateHandler::addRandomDelivery()
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
        throw std::runtime_error("sa::LevelSceneUpdateHandler::addRandomDelivery(), unknown value of DeliveryDirection was found.");
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
    std::uniform_real_distribution urd{ game_settings.getMinDeliverySpeed() , game_settings.getMaxDeliverySpeed() };
    speed = urd(random_engine);
  }

  ptrdiff_t target{};
  {
    std::uniform_int_distribution uid{ 0u, data.accessToField().getWidth() - 1u };
    target = uid(random_engine);
  }

  data.accessToDeliveries().emplace_front( direction, speed, color, target );
}

void sa::LevelSceneUpdateHandler::addBox(const sa::Delivery& _delivery)
{
  data.accessToBoxes().emplace_front(_delivery.getTarget(), 0u, game_settings.getStepperSpeed(), _delivery.getColor());
}

void sa::LevelSceneUpdateHandler::addShards(const sa::Box& _box)
{
  // TODO: Take this info from game settings.
  std::uniform_real_distribution distribution_for_x{ 0.f, 1.f };
  std::uniform_real_distribution distribution_for_y{ 0.f, 1.f };
  std::uniform_real_distribution distribution_for_angle{ 0.f, 360.f };
  std::uniform_real_distribution distribution_for_speed{ 0.1f, 0.4f };
  std::uniform_real_distribution distribution_for_av{ 0.3f, 1.f };

  for (size_t s = 0; s < game_settings.getShardsCount(); ++s)
  {
    const float x = _box.getRepresentedX() + distribution_for_x(random_engine);
    const float y = _box.getRepresentedY() + distribution_for_y(random_engine);

    const float angle = distribution_for_angle(random_engine);
    const float speed = distribution_for_speed(random_engine);
    const float vx = speed * cos(angle);
    const float vy = speed * sin(angle);

    const float a = 1.f;
    const float va = distribution_for_av(random_engine);

    const sf::Color color = _box.getColor();

    data.accessToShards().emplace_back(x, y, vx, vy, a, va, color);
  }
}

void sa::LevelSceneUpdateHandler::addProfit(const sa::Box& _box)
{
  // TODO.

  data.accessToProfits().push_front(Profit{ 100, _box.getRepresentedX() + 0.5f, _box.getRepresentedY() + 0.5f, 0.5f });
}