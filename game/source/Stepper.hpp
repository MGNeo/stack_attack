#pragma once

namespace sa
{
  class Stepper
  {
  public:

    Stepper(const size_t _x, const size_t _y);

    virtual bool isReadyToStep() const final;
    
    virtual void stepToLeft();
    virtual void stepToRight();
    virtual void stepToUp();
    virtual void stepToDown();

    virtual size_t getPreviousX() const final;
    virtual size_t getPreviousY() const final;

    virtual size_t getNextX() const final;
    virtual size_t getNextY() const final;

    virtual float getX() const final;
    virtual float getY() const final;

    virtual void addProgress(const float _dt);

    virtual ~Stepper();

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
