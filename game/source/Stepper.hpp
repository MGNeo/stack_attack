#pragma once

#include <cstdint>

namespace sa
{
  class Stepper
  {
  public:

    Stepper(const ptrdiff_t _x, const ptrdiff_t _y);

    bool isReadyToStep() const;
    
    void stepToLeft();
    void stepToRight();
    void stepToUp();
    void stepToDown();

    void fix();

    ptrdiff_t getSourceX() const;
    ptrdiff_t getSourceY() const;

    ptrdiff_t getDestinationX() const;
    ptrdiff_t getDestinationY() const;

    float getRepresentedX() const;
    float getRepresentedY() const;

    void process(const float _dt);

  private:

    static constexpr float MIN_PROGRESS = 0.f;
    static constexpr float MAX_PROGRESS = 1.f;

    ptrdiff_t source_x;
    ptrdiff_t source_y;

    float progress;

    ptrdiff_t destination_x;
    ptrdiff_t destination_y;

  };
}
