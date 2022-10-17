#include <stdio.h>
#include <wayland-server.h>

int main(int argc, char *argv[]) {
  struct wl_display *display = wl_display_create();

  printf("Hello, Compositor!\n");
  wl_display_run(display);

  return 0;
}
