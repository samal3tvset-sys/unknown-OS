#include "userspace.hpp"

namespace UnknownOS {

static UserspaceInfo userspace = {
"UnknownOS Userspace",
UserspaceState::Uninitialized,
0
};

bool userspace_init()
{
if (userspace.state != UserspaceState::Uninitialized) {
return false;
}

userspace.process_count = 0;
userspace.state = UserspaceState::Ready;

return true;

}

bool userspace_start()
{
if (userspace.state != UserspaceState::Ready) {
return false;
}

userspace.state = UserspaceState::Running;

return true;

}

bool userspace_register_process()
{
if (userspace.state != UserspaceState::Running) {
return false;
}

if (userspace.process_count == UINT32_MAX) {
    userspace.state = UserspaceState::Error;
    return false;
}

userspace.process_count++;

return true;

}

UserspaceInfo userspace_get_info()
{
return userspace;
}

void userspace_stop()
{
if (userspace.state == UserspaceState::Running) {
userspace.process_count = 0;
userspace.state = UserspaceState::Ready;
}
}

}