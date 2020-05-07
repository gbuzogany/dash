workspace(name = "com_gbuzogany_dash")

load("//:bazel/repositories.bzl", "dash_repositories")
dash_repositories()

# swift deps

# load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")
# load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

# git_repository(
#     name = "build_bazel_rules_swift",
#     remote = "https://github.com/bazelbuild/rules_swift.git",
#     commit = "ebef63d4fd639785e995b9a2b20622ece100286a",
# )

# git_repository(
#     name = "build_bazel_apple_support",
#     remote = "https://github.com/bazelbuild/apple_support.git",
#     commit = "8c585c66c29b9d528e5fcf78da8057a6f3a4f001",
# )


# load(
#     "@build_bazel_rules_swift//swift:repositories.bzl",
#     "swift_rules_dependencies",
# )

# swift_rules_dependencies()

# load(
#     "@build_bazel_apple_support//lib:repositories.bzl",
#     "apple_support_dependencies",
# )

# apple_support_dependencies()

# load(
#     "@com_google_protobuf//:protobuf_deps.bzl",
#     "protobuf_deps",
# )

# protobuf_deps()

# end swift deps
# grpc deps
load("@com_github_grpc_grpc//bazel:grpc_deps.bzl", "grpc_deps")

grpc_deps()

load("@com_github_grpc_grpc//bazel:grpc_extra_deps.bzl", "grpc_extra_deps")
grpc_extra_deps()

# end grpc deps

new_local_repository(
    name = "sdl2",
    path = "/usr/local/lib/",
    build_file_content = """
package(default_visibility = ["//visibility:public"])

cc_library(
    name = "lib",
    srcs = ["libSDL2.dylib"]
)
"""
)

new_local_repository(
    name = "sdl2_headers",
    path = "/usr/local/Cellar/sdl2/2.0.12_1/include",
    build_file_content = """
package(default_visibility = ["//visibility:public"])

cc_library(
    name = "headers",
    hdrs = glob(["**/*.h"])
)
"""
)

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

new_local_repository(
    name = "glm",
    path = "/usr/local/Cellar/glm/0.9.9.5/include",
    build_file_content = """
package(default_visibility = ["//visibility:public"])

cc_library(
    name = "headers",
    hdrs = glob(["**/*.h", "**/*.hpp", "**/*.inl"])
)
"""
)
