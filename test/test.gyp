{
    "includes": [
        "../common.gypi",
    ],
    "targets":
    [
        {
            "target_name": "unit_test",
            "type": "executable",
            "dependencies": [
                "../src/cs/cs.gyp:cs",
                "../vendor/libuv/uv.gyp:libuv",
            ],
            "sources": [
                "main.cpp",
                "message.cpp",
                "core_coder.cpp",
                "protocolstate.cpp",
                "share.cpp",
                "utils.cpp",
                "vclock.cpp",
                "sqlite3pp.cpp",
                "daemon.cpp",
                "conf.cpp",
                "uvpp.cpp",
                "clearskiesprotocol.cpp",
                "bytestream.cpp",
            ],
            "include_dirs": [
                "../src",
                "../vendor",
            ],
            "link_settings": {
                "libraries": [
                    "-lboost_unit_test_framework",
                    "-lsqlite3",
                    "-lboost_system",
                    "-lboost_filesystem",
                    #"-luv",
                ],
            },
        },
    ],
}
