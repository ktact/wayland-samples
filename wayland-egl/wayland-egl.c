#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <wayland-client-protocol.h>
#include <wayland-client.h>

static void global_object_is_ready(void *data, struct wl_registry *registry, uint32_t id, const char *interface, uint32_t version) {
}

static void global_object_has_been_removed(void *data, struct wl_registry *registry, uint32_t id) {

}

static struct wl_registry_listener registry_listener = {
  global_object_is_ready,
  global_object_has_been_removed
};

static void disable_wayland_debug_log() {
  putenv("WAYLAND_DEBUG=0");
}

int main() {
  disable_wayland_debug_log();

  struct wl_display *display = wl_display_connect(NULL);
  assert(display);

  struct wl_registry *registry = wl_display_get_registry(display);
  assert(registry);
  wl_registry_add_listener(registry, &registry_listener, NULL);

  // IMPORTANT: Wait for the server to process the request
  wl_display_roundtrip(display);

  wl_display_disconnect(display);

  return 0;
}
