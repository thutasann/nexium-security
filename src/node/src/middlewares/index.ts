import { NextFunction, Request, Response } from 'express'
import {
  sanitizeInput as sanitizeInputFn,
  filterRequest as filterRequestFn,
  setBlacklistedIPs,
  setMaliciousDomains,
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
}
