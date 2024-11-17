import {
  stream_encrypt,
  stream_decrypt,
  storeSecret as storeSecretFn,
  retrieveSecret as retrieveSecretFn,
} from '../../build/Release/nexium-security.node'

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
   * @example
   * const decrypted = NStreamCipher.decrypt(encrypted, key);
   */
  static decrypt<T>(encrypted: string, key: string) {
    return stream_decrypt<T>(encrypted, key)
  }

  /**
   * Store Secret
   * @param input - given input
   * @param key - security key
   * @example
   * const key = 'mysecurekey';
   * const secret = 'SensitiveData';
   * const encryptedSecret = NStreamCipher.storeSecret(secret, key);
   */
  static storeSecret(input: string, key: string) {
    return storeSecretFn(input, key)
  }

  /**
   * Retrieve Secret
   * @param encrypted - encrypted input
   * @param key - key
   * @example
   * const decrypted = NStreamCipher.retrieveSecret(encrypted, key);
   */
  static retrieveSecret<T>(encrypted: string, key: string) {
    return retrieveSecretFn<T>(encrypted, key)
  }
}
