// @ts-check
const { NXor } = require('../../lib')
const { stringified_json } = require('./utils/constants')
const { benchmark_args, xorEncryptDecrypt } = require('./utils/index')
const { updateResult } = require('./utils/update_readme')

const iterations = 100
const input = '{"user":{"name":"John","age":30},"message":"Welcome!"}'
const key = 'mySecureKey'
const encrypted_string = '5iZ5F9Y+ZTPLaM/CFIzkUJm+tncMHa/144QFzd0GcyzKBBRypU0EVK5K9eBD6Ygz9tPTVi5g'

/** XOR Benchmark Test */
async function xor_benchmark_test() {
  console.log('XOR Benchmark Test ==> ')

  /** Prepare the results array for table @type { any } */
  const results = []

  const result = NXor.encrypt(input, key)
  console.log('result', result)

  // ----------- Encrypt Time
  const nApiEncryptTime = benchmark_args(() => NXor.encrypt(input, key), [], iterations)
  const jsEncryptTime = benchmark_args(() => xorEncryptDecrypt(input, key), [], iterations)
  results.push({ Method: 'Nexium encrypt time', Time: nApiEncryptTime.toFixed(3) })
  results.push({ Method: 'Javascript encrypt time', Time: jsEncryptTime.toFixed(3) })
  results.push({})

  const nApiDecryptTime = benchmark_args(() => NXor.decrypt(encrypted_string, key), [], iterations)
  const jsDecryptTime = benchmark_args(() => xorEncryptDecrypt(encrypted_string, key), [], iterations)
  results.push({ Method: 'Nexium decrypt time', Time: nApiDecryptTime.toFixed(3) })
  results.push({ Method: 'Javascript decrypt time', Time: jsDecryptTime.toFixed(3) })
  results.push({})

  await updateResult(results, './results/xor.md', 'XOR Benchmark')
}

module.exports = { xor_benchmark_test }
