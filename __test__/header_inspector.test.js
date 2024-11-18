// @ts-check
const request = require('supertest')
const app = require('../express/app')

describe('Header Inspection Middleware', () => {
  it('should block requests with insecure headers', async () => {
    const response = await request(app).get('/').set('X-Insecure-Header', 'malicious value')

    expect(response.status).toBe(400)
    expect(response.text).toBe('Blocked due to insecure headers.')
  })

  it('should allow requests with valid headers', async () => {
    const response = await request(app).get('/').set('Custom-Header', 'valid value')

    expect(response.status).toBe(200)
    expect(response.text).toBe('Hello, World!')
  })

  it('should add security headers to the response', async () => {
    const response = await request(app).get('/')

    expect(response.headers['strict-transport-security']).toBe('max-age=31536000; includeSubDomains; preload')
  })
})