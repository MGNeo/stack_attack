#pragma once

#include <memory>
#include <list>

namespace sa
{

  class Particle
  {
  public:

    using Uptr = std::unique_ptr<Particle>;
    using UList = std::list<Uptr>;

    virtual ~Particle();

  };
}
