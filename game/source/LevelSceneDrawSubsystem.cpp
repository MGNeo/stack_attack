#include <LevelSceneDrawSubsystem.hpp>

sa::LevelSceneDrawSubsystem::LevelSceneDrawSubsystem(const LevelSceneDrawSubsystemLinks& _links)
  :
  links{ _links }
{
}

void sa::LevelSceneDrawSubsystem::draw(const Drawer& _drawer) const
{ 
  drawPlayer(_drawer);
  drawBoxes(_drawer);
  drawDeliveries(_drawer);
}

void sa::LevelSceneDrawSubsystem::drawDeliveries(const Drawer& _drawer) const
{
  sf::Texture boxTexture = links.getResourceLibrary().getTexture("Box.png");
  sf::Texture deliveryTexture = links.getResourceLibrary().getTexture("Delivery.png");

  sf::Sprite boxSprite;
  boxSprite.setTexture(boxTexture, true);
  boxSprite.setScale(8.f, 8.f);

  sf::Sprite deliverySprite;
  deliverySprite.setTexture(deliveryTexture, true);
  deliverySprite.setScale(8.f, 8.f);

  const ptrdiff_t begin_cell = -1;
  const ptrdiff_t end_cell = links.getField().getWidth();
  // Signed overflow is possible but it is impossible.
  const ptrdiff_t cell_difference = end_cell - begin_cell;

  for (const auto& delivery : links.getDeliveries())
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

void sa::LevelSceneDrawSubsystem::drawBoxes(const Drawer& _drawer) const
{
  sf::Texture texture = links.getResourceLibrary().getTexture("Box.png");

  sf::Sprite sprite;
  sprite.setTexture(texture, true);

  //const float x_scale = 64.f / static_cast<float>(texture.getSize().x);
  //const float y_scale = 64.f / static_cast<float>(texture.getSize().y);

  sprite.setScale(8.f, 8.f);

  for (const auto& box : links.getBoxes())
  {
    sprite.setColor(box.getColor());
    sprite.setPosition(box.getRepresentedX() * 64.f, box.getRepresentedY() * 64.f);

    _drawer.draw(sprite);
  }
}

void sa::LevelSceneDrawSubsystem::drawPlayer(const Drawer& _drawer) const
{
  sf::Texture texture = links.getResourceLibrary().getTexture("Player.png");

  sf::Sprite sprite;
  sprite.setTexture(texture, true);
  sprite.setScale(8, 8);

  sprite.setPosition(links.getPlayer().getRepresentedX() * 64.f, (links.getPlayer().getRepresentedY() - 1) * 64.f);
  _drawer.draw(sprite);
}