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
  drawProfits();
  drawPlayer();
}

void sa::LevelSceneDrawHandler::drawBoxes() const
{
  sf::Texture texture = resource_library.getTexture("Box.png");

  sf::Sprite sprite;
  sprite.setTexture(texture, true);

  const float x_scale = game_settings.getCellSize() / texture.getSize().x;
  const float y_scale = game_settings.getCellSize() / texture.getSize().y;

  sprite.setScale(x_scale, y_scale);

  for (const auto& box : data.accessToBoxes())
  {
    sprite.setColor(box.getColor());

    const float represented_x = box.getRepresentedX() * game_settings.getCellSize();
    const float represented_y = box.getRepresentedY() * game_settings.getCellSize();

    sprite.setPosition(represented_x, represented_y);

    drawer.draw(sprite);
  }
}

void sa::LevelSceneDrawHandler::drawDeliveries() const
{
  sf::Texture box_texture = resource_library.getTexture("Box.png");
  sf::Sprite box_sprite;
  box_sprite.setTexture(box_texture, true);

  {
    const float x_scale = game_settings.getCellSize() / box_texture.getSize().x;
    const float y_scale = game_settings.getCellSize() / box_texture.getSize().y;

    box_sprite.setScale(x_scale, y_scale);
  }

  sf::Texture delivery_texture = resource_library.getTexture("Delivery.png");
  sf::Sprite delivery_sprite;
  delivery_sprite.setTexture(delivery_texture, true);
  
  {
    const float x_scale = game_settings.getCellSize() / delivery_texture.getSize().x;
    const float y_scale = (0.5f * game_settings.getCellSize()) / delivery_texture.getSize().y;

    delivery_sprite.setScale(x_scale, y_scale);
  }

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

    represented_x *= game_settings.getCellSize(), 0.f;

    if (delivery.hasBox() == true)
    {
      box_sprite.setColor(delivery.getColor());
      box_sprite.setPosition(represented_x, 0.f);
      drawer.draw(box_sprite);
    }

    delivery_sprite.setPosition(represented_x, 0.f);
    drawer.draw(delivery_sprite);
  }
}

void sa::LevelSceneDrawHandler::drawShards() const
{
  sf::RectangleShape rectangle;

  rectangle.setSize({game_settings.getShardSize(), game_settings.getShardSize()});

  // TODO: Set origin to center.

  for (auto& shard : data.accessToShards())
  {
    sf::Color represented_color = shard.getColor();
    represented_color.a = static_cast<sf::Uint8>(shard.getA() * 255u);
    rectangle.setFillColor(represented_color);

    const float represented_x = shard.getX() * game_settings.getCellSize();
    const float represented_y = shard.getY() * game_settings.getCellSize();

    rectangle.setPosition(represented_x, represented_y);

    drawer.draw(rectangle);
  }
}

void sa::LevelSceneDrawHandler::drawProfits() const
{
  sf::Text text;

  text.setFont(resource_library.getFont("Default.ttf"));

  // TODO: Take this info from game settings.
  text.setCharacterSize(25);

  for (const auto& profit : data.accessToProfits())
  {
    text.setString(std::to_string(profit.getCount()));

    sf::Color represented_color = sf::Color::White;
    represented_color.a = static_cast<sf::Uint8>(profit.getA() * 255u);
    text.setFillColor(represented_color);

    const auto local_bounds = text.getLocalBounds();
    text.setOrigin(local_bounds.width / 2.f, local_bounds.height / 2.f);

    const float represented_x = profit.getX() * game_settings.getCellSize();
    const float represented_y = profit.getY() * game_settings.getCellSize();

    text.setPosition(represented_x, represented_y);

    drawer.draw(text);
  }
}

void sa::LevelSceneDrawHandler::drawPlayer() const
{
  sf::Texture texture = resource_library.getTexture("Player.png");

  sf::Sprite sprite;
  sprite.setTexture(texture, true);
  
  const float x_scale = game_settings.getPlayerWidth() / texture.getSize().x;
  const float y_scale = game_settings.getPlayerHeight() / texture.getSize().y;

  sprite.setScale(x_scale, y_scale);

  const float represented_x = data.accessToPlayer().getRepresentedX() * game_settings.getCellSize();
  const float represented_y = (data.accessToPlayer().getRepresentedY() - 1) * game_settings.getCellSize();

  sprite.setPosition(represented_x, represented_y);

  drawer.draw(sprite);
}
