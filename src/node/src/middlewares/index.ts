import { NextFunction, Request, Response } from 'express'
import {
  sanitizeInput as sanitizeInputFn,
  filterRequest as filterRequestFn,
  setBlacklistedIPs,
  setMaliciousDomains,
  validateHeaders,
  addSecurityHeaders,
  generateCSRFToken,
  validateCSRFToken,
} from '../../../build/Release/nexium-security.node'

/**
 * Nexium Security Middlewares
 */
export class NMiddleware {
  /**
   * Sanitize Input Middleware
   * @param req - request
   * @param res - response
   * @param next - next function
   */
  static sanitizeInput(req: Request, res: Response | any, next: NextFunction) {
    try {
      if (req.body && typeof req.body === 'object') {
        for (const key in req.body) {
          if (typeof req.body[key] === 'string') {
            req.body[key] = sanitizeInputFn(req.body[key])
          }
        }
      }
      next()
    } catch (err) {
      next(err)
    }
  }

  /**
   * Fitler Request Middleware
   * @param req - request
   * @param res - response
   * @param next - next function
   */
  static filterRequest(req: Request, res: Response | any, next: NextFunction) {
    try {
      const clientIp = req.ip || req.socket.remoteAddress
      const host = req.hostname

      if (!clientIp) {
        return next('Client IP Not found')
      } else {
        const isBlocked = filterRequestFn(clientIp, host)
        if (isBlocked) {
          return res.status(403).send('Forbidden: Your IP or domain is blacklisted.')
        }
        next()
      }
    } catch (error) {
      next(error)
    }
  }

  /**
   * Setup Filters for IPs and Domains
   * @param ips - ips array
   * @param domains - domains array
   */
  static setupFilters(ips: string[], domains: string[]) {
    setBlacklistedIPs(ips)
    setMaliciousDomains(domains)
  }

  /**
   * Header Inspection Middleware
   * - Block insecure or malicious headers.
   * - Add security headers like Strict-Transport-Security (HSTS).
   * @param req - request
   * @param res - response
   * @param next - next function
   */
  static headerInspection(req: Request, res: Response | any, next: NextFunction) {
    const isValid = validateHeaders(req.headers)
    if (!isValid) {
      return res.status(400).send('Blocked due to insecure headers.')
    }

    const securityHeaders = addSecurityHeaders()
    Object.keys(securityHeaders).forEach((key) => {
      res.setHeader(key, securityHeaders[key])
    })

    next()
  }

  /**
   * CSRF Middleware
   * @param secretKey - secret key to generate CSRF Token
   */
  static csrfMiddleware(secretKey: string) {
    if (!secretKey) {
      throw new Error('Secret key is required for CSRF middleware')
    }

    return (req: Request, res: Response | any, next: NextFunction) => {
      if (req.method === 'GET') {
        const token = generateCSRFToken(secretKey)
        console.log('token', token)
        res.setHeader('X-CSRF-Token', token)
      } else {
        const clientToken = req.headers['x-csrf-token']
        if (!clientToken || !validateCSRFToken(clientToken, secretKey)) {
          return res.status(403).send('Forbidden: Invalid CSRF Token')
        }
      }
      next()
    }
  }
}
