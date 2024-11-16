// @ts-check
const { NStreamCipher } = require('nexium-security')
const { stringified_json } = require('./utils/constants')

/** Stream Cipher Examples */
function streamCipherExample() {
  console.log('\nStream Cipher Examples ==> ')

  const key = 'mySecureKey'
  const encrypted = NStreamCipher.encrypt(stringified_json, key)
  console.log('encrypted ==> ', encrypted)

  const decrypted = NStreamCipher.decrypt(encrypted, key)
  console.log('\ndecrypted ==> ', decrypted)

  console.log('is Same ==> ', stringified_json === decrypted)
}

module.exports = { streamCipherExample }
