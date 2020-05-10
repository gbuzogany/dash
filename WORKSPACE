workspace(name = "com_gbuzogany_dash")

load("//:bazel/repositories.bzl", "dash_repositories")
dash_repositories()

# grpc deps
load("@com_github_grpc_grpc//bazel:grpc_deps.bzl", "grpc_deps")

grpc_deps()

load("@com_github_grpc_grpc//bazel:grpc_extra_deps.bzl", "grpc_extra_deps")
grpc_extra_deps()

# end grpc deps

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
