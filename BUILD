cc_library(
    name = "decmod",
    hdrs = [ "dm_english.h" ],
    srcs = [ "dm.c" ],
    copts = [
        "-Wall",
    ],
    visibility = ["//visibility:public"],
)

cc_binary(
    name = "test",
    srcs = [ "random.c" ],
    deps = [ "decmod" ],
    copts = [
        "-Wall",
    ],
    visibility = ["//visibility:public"],
)
