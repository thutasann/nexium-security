/** nexium.node module type declarations */
declare module '*.node' {
  // ----------- XOR Functionse
  export function xor_encrypt(input: string, key: string): string
  export function xor_decrypt(encrypted: string, key: string): any
}
