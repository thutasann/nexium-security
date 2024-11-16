// @ts-check
const { stream_cipher_benchmark_test } = require('./stream_cipher.benchmark')
const { xor_benchmark_test } = require('./xor.benchmark')

/** benchmark main fn */
;(async function main() {
  await xor_benchmark_test()
  await stream_cipher_benchmark_test()
})()
