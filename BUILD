package(default_visibility = ["//visibility:public"])

load("@bazel_tools//tools/build_defs/pkg:pkg.bzl", "pkg_tar")
load("@mxebzl//tools/windows:rules.bzl", "pkg_winzip")

config_setting(
    name = "windows",
    values = {
        "crosstool_top": "@mxebzl//tools/windows:toolchain",
    }
)

cc_binary(
    name = "ld39",
    data = ["//content"],
    linkopts = select({
        ":windows": [ "-mwindows", "-lSDL2main" ],
        "//conditions:default": [],
    }) + [
        "-lSDL2",
        "-lSDL2_image",
        "-lSDL2_mixer",
        "-static-libstdc++",
        "-static-libgcc",
    ],
    srcs = ["main.cc"],
    deps = [
        "@libgam//:game",
        ":title_screen",
    ],
)

pkg_winzip(
    name = "ld39-windows",
    files = [
        ":ld39",
        "//content",
    ]
)

pkg_tar(
    name = "ld39-linux",
    extension = "tgz",
    files = [
        ":ld39",
        "//content",
    ],
)

cc_library(
    name = "title_screen",
    srcs = ["title_screen.cc"],
    hdrs = ["title_screen.h"],
    deps = [
        "@libgam//:backdrop",
        "@libgam//:screen",
        "@libgam//:text",
        ":level_screen",
    ],
)

cc_library(
    name = "level_screen",
    srcs = ["level_screen.cc"],
    hdrs = ["level_screen.h"],
    deps = [
        "@libgam//:screen",
        "@libgam//:text",
        ":camera",
        ":map",
        ":parallax_backdrop",
        ":player",
    ],
)

cc_library(
    name = "player",
    srcs = ["player.cc"],
    hdrs = ["player.h"],
    deps = [
        "@libgam//:audio",
        "@libgam//:graphics",
        "@libgam//:input",
        "@libgam//:sprite",
        "@libgam//:spritemap",
        ":map",
        ":rect",
    ],
)

cc_library(
    name = "map",
    srcs = ["map.cc"],
    hdrs = ["map.h"],
    deps = [
        "@libgam//:graphics",
        "@libgam//:spritemap",
        ":item",
        ":rect",
    ],
)

cc_library(
    name = "rect",
    srcs = ["rect.cc"],
    hdrs = ["rect.h"],
)

cc_library(
    name = "camera",
    srcs = ["camera.cc"],
    hdrs = ["camera.h"],
    deps = [
        ":map",
        ":player",
    ],
)

cc_library(
    name = "parallax_backdrop",
    srcs = ["parallax_backdrop.cc"],
    hdrs = ["parallax_backdrop.h"],
    deps = [
        "@libgam//:graphics",
    ],
)

cc_library(
    name = "item",
    srcs = ["item.cc"],
    hdrs = ["item.h"],
    deps = [
        "@libgam//:graphics",
        "@libgam//:spritemap",
    ],
)

