#include <errno.h>
#include <stdio.h>
#include <sys/stat.h>

#ifdef __cplusplus
extern "C" {
#endif

static char* heap_end;

char* _sbrk(int incr) {
    extern char __heap_low; /* Defined by the linker */
    extern char __heap_top; /* Defined by the linker */
    char* prev_heap_end;
    if (heap_end == 0) {
        heap_end = &__heap_low;
    }
    prev_heap_end = heap_end;
    if (heap_end + incr > &__heap_top) {
        errno = ENOMEM;
        return (char*)-1;
    }
    heap_end += incr;
    return (char*)prev_heap_end;
}

__attribute__((used)) /* Will be optimised away otherwise... */
void _crt_init() {
    extern char __heap_low;    /* Defined by the linker */
    extern char __heap_top;    /* Defined by the linker */
    extern char __bss_start__; /* Defined by the linker */
    extern char __bss_end__;   /* Defined by the linker */
    char* s;
    heap_end = 0;
    s = &__bss_start__;
    while (s < &__bss_end__) *s++ = 0;
    s = &__heap_low;
    while (s < &__heap_top) *s++ = 0;
}

__attribute__((used)) /* Will be optimised away otherwise... */
void _crt_deinit() {}

#ifdef __cplusplus
}
#endif
