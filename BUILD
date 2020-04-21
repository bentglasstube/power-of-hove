package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "power-of-hove",
    data = ["//content"],
    linkopts = [
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
