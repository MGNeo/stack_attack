#pragma once

namespace sa
{
  class Cell
  {
  public:

    Cell();

    bool getBusy() const;
    void setBusy(const bool _busy);

  private:

    bool busy;

  };
}
