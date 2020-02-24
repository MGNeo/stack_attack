#pragma once

#include <cstdint>
#include <SFML/Graphics.hpp>
#include <DeliveryDirection.hpp>

namespace sa
{
  class Delivery
  {
  public:

    Delivery(const DeliveryDirection _direction,
             const float _speed,
             const sf::Color _color,
             const ptrdiff_t _target);

    void process(const float _dt);

    DeliveryDirection getDirection() const;
    sf::Color getColor() const;
    ptrdiff_t getTarget() const;
    float getProgress() const;
    bool hasBox() const;

    void throwBox();

  protected:

    const DeliveryDirection direction;
    const float speed;
    const sf::Color color;
    const ptrdiff_t target;

    float progress;
    bool has;

  };
}
