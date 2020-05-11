load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_proto_library")
load("@rules_java//java:defs.bzl", "java_binary", "java_lite_proto_library", "java_proto_library")
load("@rules_proto//proto:defs.bzl", "proto_library")
load("@com_github_grpc_grpc//bazel:cc_grpc_library.bzl", "cc_grpc_library")
load("@com_github_grpc_grpc//bazel:grpc_build_system.bzl", "grpc_proto_library")

alias(
    name = "windows",
    actual  = "@bazel_tools//src/conditions:windows"
)

alias(
    name = "macos",
    actual  = "@bazel_tools//src/conditions:darwin_x86_64"
)

filegroup(
    name = "textures",
    srcs = glob(["etc/textures/*.tga"])
)

filegroup(
    name = "shaders",
    srcs = glob(["etc/shaders/*.glsl"])
)

filegroup(
    name = "fonts",
    srcs = glob(["etc/fonts/*.otf", "dash/etc/fonts/*.ttf"])
)

proto_library(
    name = "dash_proto",
    srcs = ["proto/dash.proto"]
)

cc_proto_library(
    name = "dash_cc_proto",
    deps = [":dash_proto"],
    visibility = ["//visibility:public"]
)

cc_grpc_library(
    name = "dash_cc_grpc",
    srcs = [":dash_proto"],
    grpc_only = True,
    deps = [":dash_cc_proto"],
)

cc_binary(
    name = "dash_bin",
    srcs = glob(
        [
        "src/*.cpp",
        "src/*.hpp",
        "**/*.h"],
        exclude = [
            "src/dash.grpc.pb.cc",
            "src/dash.grpc.pb.h",
            "src/dash.pb.cc",
            "src/dash.pb.h"
        ]),
    copts = [
        "-Iexternal/angle_headers",
        "-Iexternal/glm",
        # the line below will get generated headers from proto
        "-Iexternal/dash_proto",
        "-Iexternal/freetype_headers",
        "-Iexternal/grpc_headers"
    ],
    deps = [
        ":dash_cc_grpc",
        "@sdl2//:SDL2",
        "@sdl2//:SDL2_hdrs",
        "@angle//:lib",
    	"@angle_headers//:headers",
        "@glm//:headers",
        "@com_github_grpc_grpc//:grpc++",
        "@org_freetype_freetype2//:freetype2"
    ],
    data = [
        "//dash:textures",
        "//dash:shaders",
        "//dash:fonts"
    ]
)