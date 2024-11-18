/** nexium.node module type declarations */
declare module '*.node' {
  export function sanitizeInput<T>(input: T): T
  export function setBlacklistedIPs(ips: string[]): void
  export function setMaliciousDomains(domains: string[]): void
  export function filterRequest(clientIp: string, host: string): boolean
  export function validateHeaders(headers: any): boolean
  export function addSecurityHeaders(): any
  export function generateCSRFToken(secretKey: string): string
  export function validateCSRFToken(clientToken: string | string[] | undefined, secretKey): boolean
}
