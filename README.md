# Rockette 🚀

Rockette (/ʁɔ.kɛt/, borrowed from French [_roquette_](https://fr.wikipedia.org/wiki/Roquette_(plante))) is an open source platform to ease development of graphical applications to embedded systems. Its purpose is to simplify development of custom displays for embedded systems using OpenGL ES 2.0. It enables development on Windows/Linux/macOS using OpenGL ES 2.0 (using [ANGLE](https://github.com/google/angle)), so you can implement everything on your favourite development platform, and then just cross-compile it to run on the target platform.

It's super light-weight, and has basic features already included:

- Basic OTF/TTF font loading/rendering
- TGA texture loader
- Basic shaders
- Simple [gRPC](https://grpc.io/) integration
- Many cool examples!

## Installation

Check [INSTALLATION.md](INSTALLATION.md).

## Integration

Rockette uses [gRPC](https://grpc.io/) to receive the data to be displayed. You can use any programming language supported by gRPC to send the data to be displayed, even over a network if you prefer.

Check [INTEGRATION.md](INTEGRATION.md).

## Development

It's written in C++ with very minimal dependencies. Development can be done on Windows, Linux or macOS, and then cross-compiled to run on a Raspberry.

Check the development environment instructions:

- [Windows](README-dev-windows.md)
- [macOS](README-dev-mac.md)
- [Linux](README-dev-linux.md)

