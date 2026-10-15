#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define PID1_VERSION "0.1.0"
#define PID1_MAX_SERVICES 16

typedef enum {
SERVICE_STOPPED = 0,
SERVICE_STARTING,
SERVICE_RUNNING,
SERVICE_FAILED
} service_state_t;

typedef struct {
const char *name;
service_state_t state;
} service_t;

static service_t services[PID1_MAX_SERVICES];
static size_t service_count = 0;
static bool init_running = false;

static bool pid1_register_service(const char *name)
{
if (name == NULL || service_count >= PID1_MAX_SERVICES) {
return false;
}

services[service_count].name = name;
services[service_count].state = SERVICE_STOPPED;
service_count++;

return true;

}

static void pid1_start_services(void)
{
for (size_t i = 0; i < service_count; i++) {
services[i].state = SERVICE_STARTING;

    /*
     * TODO:
     * Load the service executable.
     * Create a process.
     * Start scheduling it.
     */

    services[i].state = SERVICE_FAILED;
}

}

int pid1_main(void)
{
init_running = true;

/*
 * TODO:
 * Replace this placeholder with the UnknownOS logging system.
 */

if (!pid1_register_service("console")) {
    init_running = false;
    return -1;
}

if (!pid1_register_service("device-manager")) {
    init_running = false;
    return -1;
}

if (!pid1_register_service("filesystem")) {
    init_running = false;
    return -1;
}

pid1_start_services();

init_running = false;
return 0;

}