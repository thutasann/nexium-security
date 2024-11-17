{
  "targets": [
    {
      "target_name": "nexium-security",
      "sources": [
        "src/addon/addon.c",
        "src/addon/utils/xor.c",
        "src/addon/shared/xor_helper.c",
        "src/addon/xor_functions.c",

        "src/addon/utils/stream_cipher.c",
        "src/addon/shared/stream_cipher_helper.c",
        "src/addon/stream_cipher_functions.c",

        "src/addon/utils/sanitize_input.c",
        "src/addon/shared/sanitize_helper.c",
        "src/addon/middleware_functions.c"
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