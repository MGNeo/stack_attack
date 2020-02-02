#pragma once

#include "ResourceLibrary.hpp"

namespace sa
{
  class Game
  {
  public:
    void play();
  private:
    sa::ResourceLibrary resource_library;
  };
}
