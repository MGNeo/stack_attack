#include <CrashReporter.hpp>

#include <fstream>
#include <ctime>

void sa::CrashReporter::report(const std::string& _info)
{
  std::fstream file("Report.txt", std::ios_base::app);
  if (file.is_open() == true)
  {
    std::time_t time = std::time(nullptr);
    std::tm* tm = std::localtime(&time);
    if (tm != nullptr)
    {
      file << "[";

      file << tm->tm_year + 1900 << "y/";
      file << tm->tm_mon << "m/";
      file << tm->tm_mday << "d,";

      file << tm->tm_hour << "h:";
      file << tm->tm_min << "m:";
      file << tm->tm_sec << "s";
      
      file << "] ";
    }
    file << _info << std::endl;
  }
}