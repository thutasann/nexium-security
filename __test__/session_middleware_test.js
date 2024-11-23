// @ts-check
const request = require('supertest')
const app = require('../express/secure_session_app')
const { NMiddleware } = require('../lib')

describe('Session Middleware', () => {
  it('should create a new session if none exists', async () => {
    const response = await request(app).get('/')

    expect(response.headers['set-cookie']).toBeDefined()
    const sessionId = response.headers['set-cookie'][0].split('=')[1].split(';')[0]
    expect(NMiddleware.validateSessionFn(sessionId)).toBe(true)
  })

  it('should validate an existing session', async () => {
    const sessionId = NMiddleware.generateSessionIdFn()
    expect(NMiddleware.validateSessionFn(sessionId)).toBe(true)

    const response = await request(app).get('/').set('Cookie', `session_id=${sessionId}`)
    expect(response.headers['set-cookie']).toBeUndefined() // No new session created
  })

  it('should expire sessions after timeout', async () => {
    const sessionId = NMiddleware.generateSessionIdFn()
    expect(NMiddleware.validateSessionFn(sessionId)).toBe(true)

    jest.useFakeTimers()
    jest.advanceTimersByTime(3600 * 1000 + 1000)

    expect(NMiddleware.validateSessionFn(sessionId)).toBe(false)
    jest.useRealTimers()
  })
})
