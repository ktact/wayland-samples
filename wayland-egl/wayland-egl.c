#include <stdio.h>
#include <assert.h>
#include <wayland-client.h>

int main() {
  struct wl_display *display = wl_display_connect(NULL);

  assert(display);

  printf("Hello, Wayland-EGL!\n");

  wl_display_disconnect(display);

  return 0;
}
