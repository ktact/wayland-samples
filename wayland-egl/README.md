# Wayland-EGL sample
This sample shows how to implement Wayland client with EGL.

# Installation
## Pre-requisites
To compile this sample, you must have wayland library.

On Debian or Ubuntu Linux, both can be install with:
```bash
$ sudo apt install libwayland-bin libwayland-dev wayland-protocols
```
## Compilation
```bash
$ git clone https://github.com/ketact/wayland-samples.git
$ cd wayland-samples/wayland-egl
$ make
```

# Usage
If there is a wayland-server on your machine, you can see the logs as follows:
```bash
$ ./wayland-egl
[3114701.588]  -> wl_display@1.get_registry(new id wl_registry@2)
[3114701.724]  -> wl_display@1.sync(new id wl_callback@3)
[3114702.044] wl_display@1.delete_id(3)
[3114702.132] wl_registry@2.global(1, "wl_compositor", 5)
[3114702.202] wl_registry@2.global(2, "wl_drm", 2)
[3114702.254] wl_registry@2.global(3, "wl_shm", 1)
[3114702.298] wl_registry@2.global(4, "wl_output", 2)
[3114702.343] wl_registry@2.global(5, "wl_output", 2)
[3114702.389] wl_registry@2.global(6, "zxdg_output_manager_v1", 3)
[3114702.434] wl_registry@2.global(7, "wl_data_device_manager", 3)
[3114702.480] wl_registry@2.global(8, "zwp_primary_selection_device_manager_v1", 1)
[3114702.528] wl_registry@2.global(9, "gtk_primary_selection_device_manager", 1)
[3114702.575] wl_registry@2.global(10, "wl_subcompositor", 1)
[3114702.621] wl_registry@2.global(11, "xdg_wm_base", 4)
[3114702.666] wl_registry@2.global(12, "zxdg_shell_v6", 1)
[3114702.713] wl_registry@2.global(13, "gtk_shell1", 5)
[3114702.758] wl_registry@2.global(14, "wp_viewporter", 1)
[3114702.804] wl_registry@2.global(15, "zwp_pointer_gestures_v1", 3)
[3114702.871] wl_registry@2.global(16, "zwp_tablet_manager_v2", 1)
[3114702.935] wl_registry@2.global(17, "wl_seat", 5)
[3114703.001] wl_registry@2.global(18, "zwp_relative_pointer_manager_v1", 1)
[3114703.076] wl_registry@2.global(19, "zwp_pointer_constraints_v1", 1)
[3114703.144] wl_registry@2.global(20, "zxdg_exporter_v1", 1)
[3114703.213] wl_registry@2.global(21, "zxdg_importer_v1", 1)
[3114703.281] wl_registry@2.global(22, "zwp_linux_dmabuf_v1", 4)
[3114703.346] wl_registry@2.global(23, "zwp_keyboard_shortcuts_inhibit_manager_v1", 1)
[3114703.416] wl_registry@2.global(24, "zwp_text_input_manager_v3", 1)
[3114703.483] wl_registry@2.global(25, "wp_presentation", 1)
[3114703.546] wl_registry@2.global(26, "xdg_activation_v1", 1)
[3114703.611] wl_callback@3.done(27410)
```


