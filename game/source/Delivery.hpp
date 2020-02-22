#pragma once

#include <cstdint>

namespace sa
{
  class Delivery
  {
  public:

    Delivery(const ptrdiff_t _source, const ptrdiff_t _destination, const ptrdiff_t _target);

    bool isReadyToStep() const;

    void step();

    void process(const float _dt);

    float getRepresentedCurrent() const;

    bool isReadyToThrow() const;
    bool isFinish() const;

  protected:

    static constexpr float MIN_PROGRESS = 0.f;
    static constexpr float MAX_PROGRESS = 1.f;

    const ptrdiff_t source;
    const ptrdiff_t destination;
    const ptrdiff_t target;
    ptrdiff_t current;

    float progress;

    // TODO: Add color.
    // TODO: Add speed
    .
  };
}
