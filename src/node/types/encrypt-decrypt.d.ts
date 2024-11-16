/** nexium.node module type declarations */
declare module '*.node' {
  // ----------- XOR Functionse
  export function xor_encrypt(input: string, key: string): string
  export function xor_decrypt<T>(encrypted: string, key: string): T

  // ----------- Stream Cipher Functionse
  export function stream_encrypt(input: string, key: string): string
  export function stream_decrypt<T>(encrypted: string, key: string): T
}
