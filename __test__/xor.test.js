// @ts-check
const { NXor } = require('../lib')

describe('Secure XOR Encryption and Decryption', () => {
  test('Encrypt and Decrypt with valid key', () => {
    const originalText = 'Hello, World!'
    const key = 'securekey'

    const encrypted = NXor.encrypt(originalText, key)
    expect(typeof encrypted).toBe('string')
    expect(encrypted).not.toBe(originalText) // Ensure encryption alters the input

    const decrypted = NXor.decrypt(encrypted, key)
    expect(decrypted).toBe(originalText) // Ensure decryption returns the original input
  })

  test('Decrypt with incorrect key fails', () => {
    const originalText = 'Hello, World!'
    const key = 'securekey'
    const wrongKey = 'wrongkey'

    const encrypted = NXor.encrypt(originalText, key)
    expect(typeof encrypted).toBe('string')

    const decryptedWithWrongKey = NXor.decrypt(encrypted, wrongKey)
    expect(decryptedWithWrongKey).not.toBe(originalText) // Decryption with wrong key fails
  })

  test('Empty input and key', () => {
    const input = ''
    const key = ''

    const encrypted = NXor.encrypt(input, key)
    expect(encrypted).toBe('') // Encrypted result for empty input should also be empty

    const decrypted = NXor.decrypt(encrypted, key)
    expect(decrypted).toBe('') // Decrypted result for empty input should be empty
  })

  test('Key rotation uniqueness', () => {
    const text1 = 'Hello'
    const text2 = 'World'
    const key = 'securekey'

    const encrypted1 = NXor.encrypt(text1, key)
    const encrypted2 = NXor.encrypt(text2, key)

    expect(encrypted1).not.toBe(encrypted2) // Different texts should produce different results
  })

  test('Long input and key', () => {
    const input = 'A'.repeat(1000)
    const key = 'B'.repeat(256)

    const encrypted = NXor.encrypt(input, key)
    expect(encrypted.length).toBeGreaterThan(0) // Encrypted length should be greater than 0

    const decrypted = NXor.decrypt(encrypted, key)
    expect(decrypted).toBe(input)
  })

  test('Ensure Base64 format for encrypted text', () => {
    const originalText = 'Base64 Test'
    const key = 'securekey'

    const encrypted = NXor.encrypt(originalText, key)

    // Base64 strings consist of alphanumeric characters, +, /, and optionally end with =
    expect(/^[A-Za-z0-9+/]+={0,2}$/.test(encrypted)).toBe(true)

    const decrypted = NXor.decrypt(encrypted, key)
    expect(decrypted).toBe(originalText)
  })
})
