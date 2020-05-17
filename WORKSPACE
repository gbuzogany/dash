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
