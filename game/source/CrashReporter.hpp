#pragma once

#include <string>

namespace sa
{
  class CrashReporter
  {
  public:

    static void report(const std::string& _info);

  };
}

