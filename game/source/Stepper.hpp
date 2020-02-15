#pragma once

namespace sa
{
  class Stepper
  {
  public:

    Stepper(const size_t _x, const size_t _y);

    bool isReadyToStep() const;
    
    void stepToLeft();
    void stepToRight();
    void stepToUp();
    void stepToDown();

    void fix();

    size_t getSourceX() const;
    size_t getSourceY() const;

    size_t getDestinationX() const;
    size_t getDestinationY() const;

    float getRepresentedX() const;
    float getRepresentedY() const;

    void process(const float _dt);

  private:

    static constexpr float MIN_PROGRESS = 0.f;
    static constexpr float MAX_PROGRESS = 1.f;

    size_t source_x;
    size_t source_y;

    float progress;

    size_t destination_x;
    size_t destination_y;

  };
}
