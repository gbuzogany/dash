SDL2_LOCAL_PATH = "/Users/gbuzogany/Projects/sdl2"
SDL2_LOCAL_BUILD_PATH = SDL2_LOCAL_PATH + "/BUILD.bazel"

ANGLE_PATH_WINDOWS = "C:/Users/gbuzogany/Desktop/angle"
ANGLE_PATH_MAC = "/Users/gbuzogany/Personal/angle"
ANGLE_PATH_LINUX = "/home/gbuzogany/angle"

workspace(name = "com_gbuzogany_dash")
load("@bazel_tools//tools/build_defs/repo:git.bzl", "new_git_repository")

load("//:bazel/repositories.bzl", "dash_repositories")
dash_repositories()

# grpc deps
load("@com_github_grpc_grpc//bazel:grpc_deps.bzl", "grpc_deps")

grpc_deps()

load("@com_github_grpc_grpc//bazel:grpc_extra_deps.bzl", "grpc_extra_deps")
grpc_extra_deps()

# end grpc deps

new_local_repository(
    name = "sdl2_local",
    path = SDL2_LOCAL_PATH,
    build_file = SDL2_LOCAL_BUILD_PATH
)

############### ANGLE

############### MAC

new_local_repository(
    name = "angle_mac",
    path = ANGLE_PATH_MAC,
    build_file_content = """
package(default_visibility = ["//visibility:public"])

cc_library(
    name = "headers",
    hdrs = glob(["include/**/*.h", "include/**/*.inc"]),
)

cc_library(
    name = "lib",
    srcs = [
    	"out/Release/libEGL.dylib",
    	"out/Release/libGLESv2.dylib"
    ]
)
"""
)

######################## LINUX

new_local_repository(
    name = "angle_linux",
    path = ANGLE_PATH_LINUX,
    build_file_content = """
package(default_visibility = ["//visibility:public"])

cc_library(
    name = "headers",
    hdrs = glob(["include/**/*.h", "include/**/*.inc"]),
)

cc_library(
    name = "lib",
    srcs = [
    	"out/Debug/libEGL.so",
    	"out/Debug/libGLESv2.so"
    ]
)
"""
)

############### WINDOWS

new_local_repository(
    name = "angle_windows",
    path = ANGLE_PATH_WINDOWS,
    build_file_content = """
package(default_visibility = ["//visibility:public"])

cc_library(
    name = "headers",
    hdrs = glob(["include/**/*.h", "include/**/*.inc"]),
)

cc_library(
    name = "lib",
    srcs = [
      "out/Debug/libEGL.dll",
      "out/Debug/libGLESv2.dll"
    ]
)
"""
)
