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
    name = "power-of-hove",
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
        ":screens",
    ],
)

pkg_winzip(
    name = "power-of-hove-windows",
    files = [
        ":power-of-hove",
        "//content",
    ]
)

pkg_tar(
    name = "power-of-hove-linux",
    extension = "tar.gz",
    files = [
        ":power-of-hove",
        "//content",
    ],
)

cc_library(
    name = "screens",
    srcs = [
        "level_screen.cc",
        "overworld_screen.cc",
        "shop_screen.cc",
        "title_screen.cc",
    ],
    hdrs = [
        "level_screen.h",
        "overworld_screen.h",
        "shop_screen.h",
        "title_screen.h",
    ],
    deps = [
        "@libgam//:backdrop",
        "@libgam//:screen",
        "@libgam//:text",
        ":camera",
        ":game_state",
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
        ":game_state",
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
        ":game_state",
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

cc_library(
    name = "game_state",
    srcs = ["game_state.cc"],
    hdrs = ["game_state.h"],
)
