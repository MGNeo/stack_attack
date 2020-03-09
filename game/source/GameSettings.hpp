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

    float getCellSize() const;

    float getMaxFps() const;
    float getMinFps() const;

    float getMaxDt() const;
    float getMinDt() const;

    float getShardSize() const;

    float getStepperSpeed() const;

    float getMaxDeliverySpeed() const;
    float getMinDeliverySpeed() const;

    float getPlayerWidth() const;
    float getPlayerHeight() const;

    size_t getShardsCount() const;

  private:

    size_t window_width;
    size_t window_height;

    size_t field_width;
    size_t field_height;

    float cell_size;

    float max_fps;
    float min_fps;

    float max_dt;
    float min_dt;

    float shard_size;

    float stepper_speed;

    float max_delivery_speed;
    float min_delivery_speed;

    float player_width;
    float player_height;

    size_t shards_count;

  };
}
