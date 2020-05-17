load("@rules_cc//cc:defs.bzl", "cc_library", "cc_binary", "cc_proto_library")
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

alias(
    name = "linux",
    actual  = "@bazel_tools//src/conditions:linux_x86_64"
)

config_setting(
    name = "sdl2_local",
    values = {
        "define": "sdl2_source=local",
    }
)

LINKOPTS = select({
    ":windows": [
        "-DEFAULTLIB:user32",
        "-DEFAULTLIB:gdi32",
        "-DEFAULTLIB:winmm",
        "-DEFAULTLIB:imm32",
        "-DEFAULTLIB:ole32",
        "-DEFAULTLIB:oleaut32",
        "-DEFAULTLIB:version",
        "-DEFAULTLIB:uuid",
        "-DEFAULTLIB:shell32",
        "-DEFAULTLIB:advapi32",
        "-DEFAULTLIB:hid",
        "-DEFAULTLIB:setupapi",
        "-DEFAULTLIB:opengl32",
        "-DEFAULTLIB:kernel32",
    ],
    ":linux": [
        "-lSDL2",
        "-ldl"
    ],
    "//conditions:default": [],
})

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
    ),
    copts = [
        "-Iexternal/glm",
        # the line below will add to include path the headers generated from .proto
        "-Iexternal/dash_proto",
        "-Iexternal/freetype_headers",
        "-Iexternal/grpc_headers",
    ],
    deps = [
        "//glad:glad",
        ":dash_cc_grpc",
        "@glm//:headers",
        "@com_github_grpc_grpc//:grpc++",
        "@org_freetype_freetype2//:freetype2",
        "@angle_headers//:headers"
    ] + select({
        ":linux" : [
            "@sdl2_remote//:SDL2_hdrs",
        ],
        ":sdl2_local" : [
            "@sdl2_local//:SDL2_lib",
            "@sdl2_local//:SDL2_hdrs",
        ],
        "//conditions:default" : [
            "@sdl2_remote//:SDL2_lib",
            "@sdl2_remote//:SDL2_hdrs",
        ]
    }) + select({
        ":windows" : [
            "@angle_win//:lib",
        ],
        ":macos" : [
            "@angle_mac//:lib",
        ],
        ":linux" : [
            "@angle_linux//:lib",
        ]
    }),
    linkopts = LINKOPTS,
    data = [
        "//dash:textures",
        "//dash:shaders",
        "//dash:fonts"
    ]
)