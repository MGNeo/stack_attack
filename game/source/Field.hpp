#pragma once

#include <memory>
#include <Cell.hpp>

namespace sa
{
  class Field
  {
  public:

    Field(const size_t _width, const size_t _height);

    Cell& getCell(const size_t _x, const size_t _y);
    
  private:

    const size_t width;
    const size_t height;
    
    std::unique_ptr<std::unique_ptr<Cell[]>[]> cells;

  };
}
