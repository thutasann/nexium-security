import { NextFunction, Request, Response } from 'express'
import { sanitizeInput as sanitizeInputFn } from '../../../build/Release/nexium-security.node'

/**
 * Nexium Security Middlewares
 */
export class NMiddleware {
  /**
   * Sanitize Input
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
}
