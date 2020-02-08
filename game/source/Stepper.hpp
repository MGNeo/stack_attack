#pragma once

namespace sa
{
  class Stepper
  {
  public:

    Stepper(const size_t _x, const size_t _y);

    void addProgress(const float _dt);
    
    bool isReady() const;
    
    void toLeft();
    void toRight();
    void toUp();
    void toDown();

    size_t getPreviousX() const;
    size_t getPreviousY() const;

    size_t getNextX() const;
    size_t getNextY() const;

    float getX() const;
    float getY() const;

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
