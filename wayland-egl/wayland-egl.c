#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <wayland-client-protocol.h>
#include <wayland-client.h>

typedef struct GlobalObject GlobalObject;
struct GlobalObject {
  struct wl_compositor *compositor;
  struct wl_shell *shell;
};

typedef struct Display Display;
struct Display {
  struct wl_display *wl_display;
  struct wl_registry *registry;
};

static void global_object_is_ready(void *data, struct wl_registry *registry, uint32_t id, const char *interface, uint32_t version) {
  GlobalObject *global = (GlobalObject *)data;

  if (!strcmp(interface, "wl_compositor")) {
    global->compositor = wl_registry_bind(registry, id, &wl_compositor_interface, 1);
  } else if (!strcmp(interface, "wl_shell")) {
    global->shell = wl_registry_bind(registry, id, &wl_shell_interface, 1);
  }
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
  Display      display       = {0};
  GlobalObject global_object = {0};

  disable_wayland_debug_log();

  display.wl_display = wl_display_connect(NULL);
  assert(display.wl_display);

  display.registry = wl_display_get_registry(display.wl_display);
  assert(display.registry);

  wl_registry_add_listener(display.registry, &registry_listener, &global_object);

  // IMPORTANT: Wait for the server to process the request
  wl_display_roundtrip(display.wl_display);
  assert(global_object.compositor);
  assert(global_object.shell);

  wl_display_disconnect(display.wl_display);

  return 0;
}
