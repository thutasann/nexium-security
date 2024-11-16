// @ts-check
const { NXor } = require('nexium-security')

/** XOR Examples */
function xorExamples() {
  console.log('\nXOR Examples ==> ')
  const input = '{"user":{"name":"John","age":30},"message":"Welcome!"}'
  const key = 'mySecureKey'
  const encrypted = NXor.encrypt(input, key)
  console.log('encrypted', encrypted)

  const decrypted = NXor.decrypt(encrypted, key)
  console.log('decrypted', JSON.parse(decrypted))
}

module.exports = { xorExamples }
