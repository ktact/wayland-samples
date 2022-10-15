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
If there is a wayland-server on your machine, you can see "Hello, Wayland-EGL!" after executing the sample.
```bash
$ ./wayland-egl
Hello, Wayland-EGL!
```


