#pragma once

#include <SFML/Graphics.hpp>
#include <Stepper.hpp>
#include <list>

namespace sa
{
  class Box : public Stepper
  {
  public:

    using List = std::list<Box>;

    Box(const ptrdiff_t _x,
        const ptrdiff_t _y,
        const float _speed,
        const sf::Color _color = sf::Color::White);

    const sf::Color& getColor() const;

    bool isMarked() const;
    void toMark();

  private:

    const sf::Color color;

    bool mark;

  };
}
