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

# new_local_repository(
#     name = "sdl2",
#     path = "/Users/gbuzogany/Projects/sdl2/bazel-bin",
#     build_file_content = """
# package(default_visibility = ["//visibility:public"])

# cc_library(
#     name = "SDL2",
#     srcs = ["SDL2.dylib"]
# )
# """
# )

# new_local_repository(
#     name = "sdl2_headers",
#     path = "/Users/gbuzogany/Projects/sdl2/include",
#     build_file_content = """
# package(default_visibility = ["//visibility:public"])

# cc_library(
#     name = "headers",
#     hdrs = glob(["**/*.h"])
# )
# """
# )


new_local_repository(
    name = "sdl2",
    path = "/Users/gbuzogany/Projects/sdl2",
    build_file = "/Users/gbuzogany/Projects/sdl2/BUILD.bazel"
)

# new_local_repository(
#     name = "sdl2",
#     path = "/home/gbuzogany/sdl2",
#     build_file = "/home/gbuzogany/sdl2/BUILD.bazel"
# )

############### ANGLE

new_local_repository(
    name = "angle",
    path = "/Users/gbuzogany/Personal/angle",
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

new_local_repository(
    name = "angle_headers",
    path = "/Users/gbuzogany/Personal/angle/include",
    build_file_content = """
package(default_visibility = ["//visibility:public"])

cc_library(
    name = "headers",
    hdrs = glob(["**/*.h", "**/*.inc"]),
)
"""
)

#############################

# new_local_repository(
#     name = "angle",
#     path = "/home/gbuzogany/angle",
#     build_file_content = """
# package(default_visibility = ["//visibility:public"])

# cc_library(
#     name = "headers",
#     hdrs = glob(["include/**/*.h", "include/**/*.inc"]),
# )

# cc_library(
#     name = "lib",
#     srcs = [
#     	"out/Debug/libEGL.so",
#     	"out/Debug/libGLESv2.so"
#     ]
# )
# """
# )

# new_local_repository(
#     name = "angle_headers",
#     path = "/home/gbuzogany/angle/include",
#     build_file_content = """
# package(default_visibility = ["//visibility:public"])

# cc_library(
#     name = "headers",
#     hdrs = glob(["**/*.h", "**/*.inc"]),
# )
# """
# )


new_git_repository(
    name = "glfw",
    remote = "https://github.com/glfw/glfw.git",
    commit = "8d7e5cdb49a1a5247df612157ecffdd8e68923d2",
    build_file = "@com_gbuzogany_dash//bazel/third_party:glfw.BUILD",
)