#ifndef C_OOKIECLIKER_FILESYSTEM_H
#define C_OOKIECLIKER_FILESYSTEM_H

#if __has_include(<filesystem>)
#include <filesystem>
namespace fs = std::filesystem;
#elif __has_include(<experimental/filesystem>)
#include <experimental/filesystem>
  namespace fs = std::experimental::filesystem;
#else
  error "Missing the <filesystem> header."
#endif

#endif //C_OOKIECLIKER_FILESYSTEM_H
