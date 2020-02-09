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

    size_t getPreviousX() const;
    size_t getPreviousY() const;

    size_t getNextX() const;
    size_t getNextY() const;

    float getX() const;
    float getY() const;

    void addProgress(const float _dt);

  private:

    static constexpr float MIN_PROGRESS = 0.f;
    static constexpr float MAX_PROGRESS = 1.f;

    size_t previous_x;
    size_t previous_y;

    float progress;

    size_t next_x;
    size_t next_y;

  };
}
