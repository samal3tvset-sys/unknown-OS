#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct {
uint8_t *memory;
size_t capacity;
size_t offset;
} arena_t;

static arena_t kernel_arena;

bool arena_init(void *memory, size_t capacity)
{
if (memory == NULL || capacity == 0) {
return false;
}

kernel_arena.memory = memory;
kernel_arena.capacity = capacity;
kernel_arena.offset = 0;

return true;

}

void *arena_alloc(size_t size, size_t alignment)
{
uintptr_t base;
uintptr_t current;
uintptr_t aligned;
size_t padding;

if (kernel_arena.memory == NULL ||
    size == 0 ||
    alignment == 0 ||
    (alignment & (alignment - 1)) != 0) {
    return NULL;
}

base = (uintptr_t)kernel_arena.memory;
current = base + kernel_arena.offset;

padding = (size_t)((-(uintptr_t)current) & (alignment - 1));

if (padding > kernel_arena.capacity - kernel_arena.offset) {
    return NULL;
}

if (size > kernel_arena.capacity -
    kernel_arena.offset - padding) {
    return NULL;
}

aligned = current + padding;

kernel_arena.offset += padding + size;

return (void *)aligned;

}

void arena_reset(void)
{
kernel_arena.offset = 0;
}

size_t arena_used(void)
{
return kernel_arena.offset;
}

size_t arena_remaining(void)
{
return kernel_arena.capacity - kernel_arena.offset;
}