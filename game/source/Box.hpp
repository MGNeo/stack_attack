#pragma once

#include <SFML/Graphics.hpp>
#include <Stepper.hpp>

namespace sa
{
  class Box : public Stepper
  {
  public:

    Box(const ptrdiff_t _x, const ptrdiff_t _y, const sf::Color _color = sf::Color::White);

    const sf::Color& getColor() const;

    bool isMarked() const;
    void toMark();

  private:

    const sf::Color color;

    bool mark;

  };
}
