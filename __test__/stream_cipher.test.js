// @ts-check
const { NStreamCipher } = require('../lib')

describe('Stream Cipher RC4 Encryption/Decryption', () => {
  test('Encrypt and Decrypt with valid key', () => {
    const originalText = 'Hello, World!'
    const key = 'securekey'

    const encrypted = NStreamCipher.encrypt(originalText, key)
    expect(typeof encrypted).toBe('string')
    expect(encrypted).not.toBe(originalText) // Ensure encryption alters the input

    const decrypted = NStreamCipher.decrypt(encrypted, key)
    expect(decrypted).toBe(originalText) // Ensure decryption returns the original input
  })

  test('Decrypt with incorrect key fails', () => {
    const originalText = 'Hello, World!'
    const key = 'securekey'
    const wrongKey = 'wrongkey'

    const encrypted = NStreamCipher.encrypt(originalText, key)
    expect(typeof encrypted).toBe('string')

    const decryptedWithWrongKey = NStreamCipher.decrypt(encrypted, wrongKey)
    expect(decryptedWithWrongKey).not.toBe(originalText) // Decryption with wrong key fails
  })

  test('Empty input and key', () => {
    const input = ''
    const key = ''

    const encrypted = NStreamCipher.encrypt(input, key)
    expect(encrypted).toBe('') // Encrypted result for empty input should also be empty

    const decrypted = NStreamCipher.decrypt(encrypted, key)
    expect(decrypted).toBe('') // Decrypted result for empty input should be empty
  })

  test('Long input and key', () => {
    const input = 'A'.repeat(1000)
    const key = 'B'.repeat(256)

    const encrypted = NStreamCipher.encrypt(input, key)
    expect(encrypted.length).toBeGreaterThan(0) // Encrypted length should be greater than 0

    const decrypted = NStreamCipher.decrypt(encrypted, key)
    expect(decrypted).toBe(input)
  })
})

test('Securely store and retrieve a secret', () => {
  const key = 'mysecurekey'
  const secret = 'SensitiveData'

  const encryptedSecret = NStreamCipher.storeSecret(secret, key)

  const decryptedSecret = NStreamCipher.retrieveSecret(encryptedSecret, key)

  expect(decryptedSecret).toBe(secret)
})
