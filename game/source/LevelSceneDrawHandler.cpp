#include <LevelSceneDrawHandler.hpp>

sa::LevelSceneDrawHandler::LevelSceneDrawHandler(ResourceLibrary& _resource_library,
                                                 const Drawer& _drawer,
                                                 LevelSceneData& _data,
                                                 const GameSettings& _game_settings)
  :
  resource_library{ _resource_library },
  drawer{ _drawer },
  data{ _data},
  game_settings{ _game_settings }
{
}

void sa::LevelSceneDrawHandler::draw() const
{
  drawBoxes();
  drawDeliveries();
  drawShards();
  drawPlayer();
}

void sa::LevelSceneDrawHandler::drawBoxes() const
{
  sf::Texture texture = resource_library.getTexture("Box.png");

  sf::Sprite sprite;
  sprite.setTexture(texture, true);

  // TODO: Take this info from game settings.
  sprite.setScale(8.f, 8.f);

  for (const auto& box : data.accessToBoxes())
  {
    sprite.setColor(box.getColor());
    sprite.setPosition(box.getRepresentedX() * game_settings.getSpriteSize(), box.getRepresentedY() * game_settings.getSpriteSize());

    drawer.draw(sprite);
  }
}

void sa::LevelSceneDrawHandler::drawDeliveries() const
{
  sf::Texture boxTexture = resource_library.getTexture("Box.png");
  sf::Texture deliveryTexture = resource_library.getTexture("Delivery.png");

  sf::Sprite boxSprite;
  boxSprite.setTexture(boxTexture, true);
  boxSprite.setScale(8.f, 8.f);

  sf::Sprite deliverySprite;
  deliverySprite.setTexture(deliveryTexture, true);
  // TODO: Correct scale according to sprite size from game settings.
  deliverySprite.setScale(8.f, 8.f);

  const ptrdiff_t begin_cell = -1;
  const ptrdiff_t end_cell = data.accessToField().getWidth();
  // Signed overflow is possible but it is impossible.
  const ptrdiff_t cell_difference = end_cell - begin_cell;

  for (const auto& delivery : data.accessToDeliveries())
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
      boxSprite.setPosition(represented_x * game_settings.getSpriteSize(), 0.f);
      drawer.draw(boxSprite);
    }

    deliverySprite.setPosition(represented_x * game_settings.getSpriteSize(), 0.f);
    drawer.draw(deliverySprite);
  }
}

void sa::LevelSceneDrawHandler::drawPlayer() const
{
  sf::Texture texture = resource_library.getTexture("Player.png");

  sf::Sprite sprite;
  sprite.setTexture(texture, true);
  // TODO: Correct scale according to sprite size from game settings.
  sprite.setScale(8, 8);

  sprite.setPosition(data.accessToPlayer().getRepresentedX() * game_settings.getSpriteSize(),
                     (data.accessToPlayer().getRepresentedY() - 1) * game_settings.getSpriteSize());
  drawer.draw(sprite);
}

void sa::LevelSceneDrawHandler::drawShards() const
{
  sf::RectangleShape rectangle;

  // TODO: Take this info from game settings.
  rectangle.setSize({ 3.f, 3.f });

  for (auto& shard : data.accessToShards())
  {
    sf::Color represented_color = shard.getColor();
    represented_color.a = static_cast<sf::Uint8>(shard.getA() * 255u);
    rectangle.setFillColor(represented_color);

    rectangle.setPosition(shard.getX() * game_settings.getSpriteSize(), shard.getY() * game_settings.getSpriteSize());

    drawer.draw(rectangle);
  }
}