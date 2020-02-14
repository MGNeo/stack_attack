#include <Field.hpp>
#include <stdexcept>

sa::Field::Field(const size_t _width, const size_t _height)
  :
  width{ _width },
  height{ _height }
{
  if (_width == 0u)
  {
    throw std::invalid_argument("sa::Field::Field(), _width == 0u.");
  }

  if (_height == 0u)
  {
    throw std::invalid_argument("sa::Field::Field(), _height == 0u.");
  }

  cells = std::make_unique<std::unique_ptr<Cell[]>[]>(width);
  for (size_t x = 0; x < width; ++x)
  {
    cells[x] = std::make_unique<Cell[]>(height);
  }
}

bool sa::Field::isCellValid(const size_t _x, const size_t _y) const
{
  if ((_x < width) && (_y < height))
  {
    return true;
  }
  return false;
}

sa::Cell& sa::Field::getCell(const size_t _x, const size_t _y)
{

  if (_x >= width)
  {
    throw std::invalid_argument("sa::Field::getCell(), _x > width.");
  }

  if (_y >= height)
  {
    throw std::invalid_argument("sa::Field::getCell(), _y > height.");
  }

  return cells[_x][_y];
}

void sa::Field::clear()
{
  for (size_t x = 0; x < width; ++x)
  {
    for (size_t y = 0; y < height; ++y)
    {
      cells[x][y].setBusy(false);
    }
  }
}

size_t sa::Field::getWidth() const
{
  return width;
}

size_t sa::Field::getHeight() const
{
  return height;
}