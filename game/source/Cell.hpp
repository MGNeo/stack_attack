#pragma once

#include <Box.hpp>

namespace sa
{
  class Cell
  {
  public:

    Cell();

    Box* getOccupyingBox() const;
    void setOccupingBox(Box* const _occupyingBox);

  private:

    bool busy;
    Box* occupyingBox;

  };
}
