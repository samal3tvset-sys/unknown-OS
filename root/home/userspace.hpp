#ifndef UNKNOWNOS_USERSPACE_HPP
#define UNKNOWNOS_USERSPACE_HPP

#include <cstdint>

namespace UnknownOS {

inline constexpr char USERSPACE_VERSION[] = "0.1.0";

enum class UserspaceState : std::uint8_t {
Uninitialized,
Ready,
Running,
Error
};

struct UserspaceInfo {
const char* name;
UserspaceState state;
std::uint32_t process_count;
};

bool userspace_init();
bool userspace_start();
bool userspace_register_process();
UserspaceInfo userspace_get_info();
void userspace_stop();

}

#endif