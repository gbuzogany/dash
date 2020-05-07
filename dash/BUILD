load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
    name = "dash",
    srcs = glob(["src/*.cpp", "src/*.cc", "src/*.hpp", "**/*.h"]),
    copts = [
        "-Iexternal/angle_headers",
    	"-Iexternal/sdl2_headers",
        "-Iexternal/glm",
        "-Iexternal/freetype_headers",
        "-Iexternal/grpc_headers"
    ],
    deps = [
        "@angle//:lib",
    	"@angle_headers//:headers",
        "@sdl2//:lib",
    	"@sdl2_headers//:headers",
        "@glm//:headers",
        "@com_google_protobuf//:protobuf",
        "@com_github_grpc_grpc//:grpc++",
        "@org_freetype_freetype2//:freetype2"
    ]
)