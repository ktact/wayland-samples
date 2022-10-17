#include <assert.h>
#include <stdio.h>
#include <wayland-server.h>

int main(int argc, char *argv[]) {
  struct wl_display *display = wl_display_create();

  const char *socket_name = wl_display_add_socket_auto(display);
  assert(socket_name);

  printf("Hello, %s!\n", socket_name);
  wl_display_run(display);

  return 0;
}
