import { stream_encrypt, stream_decrypt } from '../../build/Release/nexium-security.node'

/** Stream Cipher Methods */
export class NStreamCipher {
  /**
   * XOR Encrypt
   * @param input - given input
   * @param key - security key
   * @example
   * const input = '{"user":{"name":"John","age":30},"message":"Welcome!"}'
   * const key = 'mySecureKey'
   * const encrypted = NStreamCipher.encrypt(input, key)
   */
  static encrypt(input: string, key: string) {
    return stream_encrypt(input, key)
  }

  /**
   * XOR Decrypt
   * @param encrypted - encrypted input
   * @param key - key
   * @param salt - salt value
   * @example
   * const decrypted = NStreamCipher.decrypt(encrypted, key);
   */
  static decrypt<T>(encrypted: string, key: string) {
    return stream_decrypt<T>(encrypted, key)
  }
}
