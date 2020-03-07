#include <LevelSceneDrawHandler.hpp>

sa::LevelSceneDrawHandler::LevelSceneDrawHandler(LevelSceneData& _data)
  :
  data{ _data}
{
}

void sa::LevelSceneDrawHandler::draw(const sa::Drawer& _drawer) const
{
  drawBoxes(_drawer);
  drawDeliveries(_drawer);
  drawShards(_drawer);
  drawPlayer(_drawer);
}

void sa::LevelSceneDrawHandler::drawBoxes(const Drawer& _drawer) const
{
  sf::Texture texture = data.accessToResourceLibrary().getTexture("Box.png");

  sf::Sprite sprite;
  sprite.setTexture(texture, true);

  //const float x_scale = 64.f / static_cast<float>(texture.getSize().x);
  //const float y_scale = 64.f / static_cast<float>(texture.getSize().y);

  sprite.setScale(8.f, 8.f);

  for (const auto& box : data.accessToBoxes())
  {
    sprite.setColor(box.getColor());
    sprite.setPosition(box.getRepresentedX() * 64.f, box.getRepresentedY() * 64.f);

    _drawer.draw(sprite);
  }
}

void sa::LevelSceneDrawHandler::drawDeliveries(const sa::Drawer& _drawer) const
{
  sf::Texture boxTexture = data.accessToResourceLibrary().getTexture("Box.png");
  sf::Texture deliveryTexture = data.accessToResourceLibrary().getTexture("Delivery.png");

  sf::Sprite boxSprite;
  boxSprite.setTexture(boxTexture, true);
  boxSprite.setScale(8.f, 8.f);

  sf::Sprite deliverySprite;
  deliverySprite.setTexture(deliveryTexture, true);
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
      boxSprite.setPosition(represented_x * 64.f, 0.f);
      _drawer.draw(boxSprite);
    }

    deliverySprite.setPosition(represented_x * 64.f, 0.f);
    _drawer.draw(deliverySprite);
  }
}

void sa::LevelSceneDrawHandler::drawPlayer(const Drawer& _drawer) const
{
  sf::Texture texture = data.accessToResourceLibrary().getTexture("Player.png");

  sf::Sprite sprite;
  sprite.setTexture(texture, true);
  sprite.setScale(8, 8);

  sprite.setPosition(data.accessToPlayer().getRepresentedX() * 64.f, (data.accessToPlayer().getRepresentedY() - 1) * 64.f);
  _drawer.draw(sprite);
}

void sa::LevelSceneDrawHandler::drawShards(const Drawer& _drawer) const
{
  sf::RectangleShape rectangle;

  for (auto& shard : data.accessToShards())
  {
    rectangle.setSize({ 3.f, 3.f });

    sf::Color represented_color = shard.getColor();
    represented_color.a = static_cast<sf::Uint8>(shard.getA() * 255u);
    rectangle.setFillColor(represented_color);

    rectangle.setPosition(shard.getX() * 64.f, shard.getY() * 64.f);

    _drawer.draw(rectangle);
  }
}