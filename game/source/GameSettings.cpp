#include <GameSettings.hpp>

sa::GameSettings::GameSettings()
  :
  window_width{ 768 },
  window_height{ 600 },
  max_fps{ 120.f },
  min_fps{ 60.f },
  max_dt{ 1.f / min_fps },
  min_dt{ 1.f / max_fps }
{
}

size_t sa::GameSettings::getWindowWidth() const
{
  return window_width;
}

size_t sa::GameSettings::getWindowHeight() const
{
  return window_height;
}

size_t sa::GameSettings::getFieldWidth() const
{
  return field_width;
}

size_t sa::GameSettings::getFieldHeight() const
{
  return field_height;
}

float sa::GameSettings::getSpriteSize() const
{
  return sprite_size;
}

float sa::GameSettings::getMaxFps() const
{
  return max_fps;
}

float sa::GameSettings::getMinFps() const
{
  return min_fps;
}

float sa::GameSettings::getMaxDt() const
{
  return max_dt;
}

float sa::GameSettings::getMinDt() const
{
  return min_dt;
}