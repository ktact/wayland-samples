#include <EGL/egl.h>
#include <EGL/eglplatform.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <wayland-client-core.h>
#include <wayland-client-protocol.h>
#include <wayland-client.h>
#include <EGL/egl.h>
#include <GL/gl.h>
#include <wayland-egl-core.h>

typedef struct GlobalObject GlobalObject;
struct GlobalObject {
  struct wl_compositor *compositor;
  struct wl_shell *shell;
};

typedef struct Display Display;
struct Display {
  struct wl_display *wl_display;
  struct wl_registry *registry;
  EGLDisplay egl_display;

  // Fields for Window
  EGLContext egl_context;
  struct wl_surface *surface;
  struct wl_shell_surface *shell_surface;
  struct wl_egl_window *egl_window;
  EGLSurface egl_surface;
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

static void initializeEGL(Display *display) {
  /*
   * Get the EGL display connection for the wayland display
   * See https://registry.khronos.org/EGL/sdk/docs/man/html/eglGetDisplay.xhtml
   */
  display->egl_display = eglGetDisplay(display->wl_display);

  /*
   * Initialize the EGL display connection
   * See https://registry.khronos.org/EGL/sdk/docs/man/html/eglInitialize.xhtml
   */
  EGLBoolean initializationSuccessful = eglInitialize(display->egl_display, /* major version */NULL, /* minor version */NULL);
  assert(initializationSuccessful == EGL_TRUE);
}

static void server_pinged_to_me(void *data, struct wl_shell_surface *shell_surface, uint32_t serial) {
  // IMPORTANT: If a client do not pong, a server consider the client is freeze
  wl_shell_surface_pong(shell_surface, serial);
}

static void window_size_will_be_changed(void *data, struct wl_shell_surface *shell_surface, uint32_t edges, int32_t width, int32_t height) {
  Display *display = (Display *)data;

  wl_egl_window_resize(display->egl_display, width, height, 0, 0);
}

static void popup_window_will_be_terminated(void *data, struct wl_shell_surface *shell_surface) {

}

static struct wl_shell_surface_listener shell_surface_listener = {
  server_pinged_to_me,
  window_size_will_be_changed,
  popup_window_will_be_terminated
};

static void createWindow(Display *display, GlobalObject *global, int width, int height) {
  /*
   * Set the rendering API
   * See https://registry.khronos.org/EGL/sdk/docs/man/html/eglBindAPI.xhtml
   */
  EGLBoolean bindSuccessful = eglBindAPI(EGL_OPENGL_API);
  assert(bindSuccessful == EGL_TRUE);

  /*
   * Get a list of EGL frame buffer configurations that match specified attributes
   * See https://registry.khronos.org/EGL/sdk/docs/man/html/eglChooseConfig.xhtml
   */
  EGLint attributes[] = {
    EGL_RED_SIZE,   8,
    EGL_GREEN_SIZE, 8,
    EGL_BLUE_SIZE,  8,
    EGL_ALPHA_SIZE, 8,
    EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
    EGL_NONE
  };
  EGLConfig configures;
  EGLint num_of_configures;
  EGLBoolean chooseConfigSuccessful = eglChooseConfig(display->egl_display, attributes, &configures, /* configure size */1, &num_of_configures);
  assert(chooseConfigSuccessful == EGL_TRUE);

  display->egl_context = eglCreateContext(display->egl_display, configures, EGL_NO_CONTEXT, NULL);
  assert(display->egl_context);

  display->surface = wl_compositor_create_surface(global->compositor);
  assert(display->surface);

  display->shell_surface = wl_shell_get_shell_surface(global->shell, display->surface);
  assert(display->shell_surface);

  wl_shell_surface_add_listener(display->shell_surface, &shell_surface_listener, display->surface);
  wl_shell_surface_set_toplevel(display->shell_surface);

  display->egl_window = wl_egl_window_create(display->surface, (EGLint)width, (EGLint)height);
  assert(display->egl_window != NULL);

  display->egl_surface = eglCreateWindowSurface(display->egl_display, configures, (EGLNativeWindowType)display->egl_window, NULL);
  assert(display->egl_surface != EGL_NO_SURFACE);

  EGLBoolean makeCurrentSuccessful = eglMakeCurrent(display->egl_display, display->egl_surface, display->egl_surface, display->egl_context);
  assert(makeCurrentSuccessful == EGL_TRUE);
}

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

  initializeEGL(&display);
  createWindow(&display, &global_object, 256, 256);

  // Main loop
  while (1) {
    wl_display_dispatch_pending(display.wl_display);

    // draw
    glClearColor(1.0, 0.0, 0.0, 0.3);
    glClear(GL_COLOR_BUFFER_BIT);
    eglSwapBuffers(display.egl_display, display.egl_surface);
  }

  eglTerminate(display.egl_display);
  wl_display_disconnect(display.wl_display);

  return 0;
}
