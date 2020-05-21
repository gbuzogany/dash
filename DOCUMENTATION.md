# Rockette Documentation

## Summary

Rockette is a C++ application that is intended to be used as a starting point when developing graphical applications for embedded systems. It simplifies development, as it's already configured to be built and run on Windows/Linux/macOS with minimal effort, and already includes basic components for text rendering, texture loading and receiving data from other applications.

You are still expected to write the C++ rendering code and to use OpenGL by yourself, but all the basic plumbing has been taken care of.

It uses:

- SDL2 as a multi-platform media layer abstraction
- OpenGL ES 2.0 for rendering
- Basic gRPC integration to receive data from other applications
- ANGLE to emulate the OpenGL ES 2.0 when running on Windows/Linux/macOS
- FreeType to load TTF/OTF fonts
- Bazel for compilation

## Implementation

The `src/main.cpp` file has the entry point and rendering/event processing loop, and also where the gRPC service `RocketteService` is instantiated.

Rendering happens on `Scene` objects, that are expected to implement the interface described in the `src/Src.hpp`.

The received RPC calls are handled by the `RocketService` class, which stores received data in `std::map`s that can be easily used in the application.

### Scenes

Scenes can be queued up in the `main` function, and will be executed as they complete (when a scene `update()` call returns `false`).

The `renderFixed()` method is intended to be used to render fixed elements to a framebuffer to be reused in all other frames.

The `render()` method is expected to contain the rendering code, responsible to render the frames to be displayed.

The `update(float delta)` method is expected to contain the event handling and update logic. The `delta` parameter represents the number of seconds that passed since the last processed frame.

### Text loading / rendering

OTF/TTF fonts are supported. 

### Texture loading / rendering

Only 32-bit TGA are supported.

### Shader Programs

### RPC

