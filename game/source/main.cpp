#include <stdexcept>

#include <Game.hpp>
#include <CrashReporter.hpp>

int main([[maybe_unused]] int argc, [maybe_unused]] char** argv)
{
  try
  {
    sa::Game game;
    game.play();
  }
  catch (std::exception& exception)
  {
    sa::CrashReporter::report(exception.what());
  }
  catch (...)
  {
    sa::CrashReporter::report("Unknown exception was detected.");
  }
  return 0;
}