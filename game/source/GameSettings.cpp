#include <GameSettings.hpp>

sa::GameSettings::GameSettings()
  :
  window_width{ 768 },
  window_height{ 600 },
  field_width{ 12 },
  field_height{ 9 },
  cell_size{ 64.f },
  max_fps{ 120.f },
  min_fps{ 60.f },
  max_dt{ 1.f / min_fps },
  min_dt{ 1.f / max_fps },
  shard_size{ 4.f },
  stepper_speed{ 2.f },
  max_delivery_speed{ 0.3f },
  min_delivery_speed{ 0.05f },
  player_width{ 64.f },
  player_height{ 128.f },
  shards_count{ 10 }
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

float sa::GameSettings::getCellSize() const
{
  return cell_size;
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

float sa::GameSettings::getShardSize() const
{
  return shard_size;
}

float sa::GameSettings::getStepperSpeed() const
{
  return stepper_speed;
}

float sa::GameSettings::getMaxDeliverySpeed() const
{
  return max_delivery_speed;
}

float sa::GameSettings::getMinDeliverySpeed() const
{
  return min_delivery_speed;
}

float sa::GameSettings::getPlayerWidth() const
{
  return player_width;
}

float sa::GameSettings::getPlayerHeight() const
{
  return player_height;
}

size_t sa::GameSettings::getShardsCount() const
{
  return shards_count;
}