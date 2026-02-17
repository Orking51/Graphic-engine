//interface publique

#ifndef WINDOW_H
#define WINDOW_H

#include <stdbool.h>

bool window_init(int width, int height, const char* title);
void window_shutdown(void);

bool window_should_close(void);
void window_swap_buffers(void);
void window_poll_events(void);

#endif
