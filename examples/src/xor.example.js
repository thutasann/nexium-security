// @ts-check
const { NXor } = require('nexium-security')
const { stringified_json } = require('./utils/constants')

/** XOR Examples */
function xorExamples() {
  console.log('\nXOR Examples ==> ')

  const key = 'mySecureKey'
  const encrypted = NXor.encrypt(stringified_json, key)
  console.log('encrypted ==> ', encrypted)

  const decrypted = NXor.decrypt(encrypted, key)
  console.log('\ndecrypted ==> ', decrypted)

  console.log('is Same ==> ', stringified_json === decrypted)
}

module.exports = { xorExamples }
