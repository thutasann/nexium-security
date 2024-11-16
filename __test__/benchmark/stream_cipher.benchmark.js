// @ts-check
const { NStreamCipher } = require('../../lib')
const { stringified_json } = require('./utils/constant')
const { benchmark_args, xorEncryptDecrypt } = require('./utils/index')
const { updateResult } = require('./utils/update_readme')

const iterations = 100
const key = 'mySecureKey'
const encrypted_string =
  '5iZgAcUpKziScNqBFYywD9fG+yUZHe+y9IYM3MUPOHOKQxZkqR0JAulStuRj6dw69fyAB3t0m4PWvD3w521RB7hhLFSFP2trnWGU3lKU8BiXlfQzWU6rr/TeVITST2s2xU0ONuxLXUmnULj8MP2EL7WvxE51bMnGgOZ2vuNjSVSsOTcU1nsgZYUy0YgBzaYVhYPmLBwY+Pei3EfDz0ElMdpcWyXkWRoep160/mShlyanuZ0OcH2Oks7tc+H1OgdTsyhqF8ZjKzKFPN2KVZK1HJfEsSwSFPqj+s9J0IgWJTHaXFsi5FkbT6kev+Mho4M+rfWdDnB9jpLN7XPg9Q=='

/** Stream Cipher Benchmark Test */
async function stream_cipher_benchmark_test() {
  console.log('Stream Cipher Benchmark Test ==> ')

  /** Prepare the results array for table @type { any } */
  const results = []

  // ----------- Encrypt Time
  const nApiEncryptTime = benchmark_args(() => NStreamCipher.encrypt(stringified_json, key), [], iterations)
  results.push({ Method: 'Nexium Stream Cipher Encrypt time', Time: nApiEncryptTime.toFixed(3) })
  results.push({})

  // ----------- Decrypt Time
  const nApiDecryptTime = benchmark_args(() => NStreamCipher.decrypt(encrypted_string, key), [], iterations)
  results.push({ Method: 'Nexium Stream Cipher Decrypt time', Time: nApiDecryptTime.toFixed(3) })
  results.push({})

  await updateResult(results, './results/stream_cipher.md', 'Stream Cipher Benchmark')
}

module.exports = { stream_cipher_benchmark_test }
