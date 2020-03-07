#pragma once

namespace sa
{
  class GameSettings
  {
  public:

    GameSettings();

    size_t getWindowWidth() const;
    size_t getWindowHeight() const;

    size_t getFieldWidth() const;
    size_t getFieldHeight() const;

    float getSpriteSize() const;

    float getMaxFps() const;
    float getMinFps() const;

    float getMaxDt() const;
    float getMinDt() const;

  private:

    size_t window_width;
    size_t window_height;

    size_t field_width;
    size_t field_height;

    float sprite_size;

    float max_fps;
    float min_fps;

    float max_dt;
    float min_dt;

  };
}
