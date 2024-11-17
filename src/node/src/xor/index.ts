import { xor_encrypt, xor_decrypt } from '../../../build/Release/nexium-security.node'

/** XOR Methods */
export class NXor {
  /**
   * XOR Encrypt
   * @param input - given input
   * @param key - security key
   * @example
   * const input = '{"user":{"name":"John","age":30},"message":"Welcome!"}'
   * const key = 'mySecureKey'
   * const encrypted = NXor.encrypt(input, key)
   */
  static encrypt(input: string, key: string) {
    return xor_encrypt(input, key)
  }

  /**
   * XOR Decrypt
   * @param encrypted - encrypted input
   * @param key - key
   * @param salt - salt value
   * @example
   * const decrypted = NXor.decrypt(encrypted, key);
   */
  static decrypt<T>(encrypted: string, key: string) {
    return xor_decrypt<T>(encrypted, key)
  }
}
