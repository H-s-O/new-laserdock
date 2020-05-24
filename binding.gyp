{
  "targets": [
    {
      "target_name": "laserdocknode",
      "sources": [
        "src_native/LaserdockNode.cpp",
      ],
      "include_dirs": [
        "liblaserdock/include",
        "<!@(node -p \"require('node-addon-api').include\")"
      ],
      "link_settings": {
        "libraries": [
          "-Wl",
          "-rpath <(module_root_dir)/liblaserdock/lib",
          "-L<(module_root_dir)/liblaserdock/lib",
          "-llaserdocklib"
        ]
      },
      "defines": [ "NAPI_DISABLE_CPP_EXCEPTIONS" ],
      "cflags": [
        "-std=c++11",
        "-stdlib=libc++"
      ],
      "conditions": [
        ["OS=='mac'", {
          "cflags+": ["-fvisibility=hidden"],
          "xcode_settings": {
            "GCC_SYMBOLS_PRIVATE_EXTERN": "YES", # -fvisibility=hidden
            "OTHER_CFLAGS": [  "-std=c++11",  "-stdlib=libc++" ],
            "OTHER_LDFLAGS": [ "-stdlib=libc++" ],
          }
        }]
      ]
    }
  ]
}
