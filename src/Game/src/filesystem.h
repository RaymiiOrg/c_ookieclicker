#ifndef C_OOKIECLIKER_FILESYSTEM_H
#define C_OOKIECLIKER_FILESYSTEM_H

#if defined(__GNUC__) && __GNUC__ < 9
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#else
#include <filesystem>
namespace fs = std::filesystem;
#endif

#endif //C_OOKIECLIKER_FILESYSTEM_H
