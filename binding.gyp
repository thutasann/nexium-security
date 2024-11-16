{
  "targets": [
    {
      "target_name": "nexium-security",
      "sources": [
        "src/addon/addon.c",
        "src/addon/utils/xor.c",
        "src/addon/shared/xor_helper.c",
        "src/addon/xor_functions.c"
      ],
      "include_dirs": [
        "<!@(node -e \"require('node-addon-api').include\")"
      ],
      "cflags!": ["-fno-exceptions"],
      "cflags": [
        "-std=c11",
        "-Os",
        "-ffunction-sections",
        "-fdata-sections",
        "-flto"
      ],
      "ldflags": [
        "-Wl,--gc-sections",
        "-Wl,--strip-all",
        "-s",
        "-flto"
      ]
    }
  ]
}