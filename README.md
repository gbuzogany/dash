# Rockette

Rockette is an open source automotive dashboard display platform. You can use it to make a custom dashboard for your car, motorcycle, driving simulator setup, or anything else that you find it useful for.

You can either use one of the already implemented display layouts to display your data, or create your own.

It can be run in any Linux system with OpenGL ES 2.0 support (for example: a Raspberry Pi with a display).

It's super light-weight, and as it uses OpenGL, you can use it to render pretty much any graphical effects.

## Installation

Check [INSTALLATION.md](INSTALLATION.md).

## Integration

Rockette uses [gRPC](https://grpc.io/) to receive the data to be displayed. You can use any programming language supported by gRPC to send the data to be displayed, even over a network if you prefer.

## Development

It's written in C++ with very minimal dependencies. Development can be done on Windows, Linux or macOS, and then cross-compiled to run on a Raspberry.