// @ts-check
const request = require('supertest')
const app = require('../express/app')

describe('Sanitize Middleware', () => {
  test('Sanitizes and escapes dangerous characters', async () => {
    const response = await request(app)
      .post('/submit')
      .send({ name: '<script>alert("xss")</script>', comment: 'Hello & Goodbye' })

    expect(response.body.sanitizedBody).toEqual({
      name: '&lt;script&gt;alert(&quot;xss&quot;)&lt;/script&gt;',
      comment: 'Hello &amp; Goodbye',
    })
  })

  test('Leaves normal strings unchanged', async () => {
    const response = await request(app).post('/submit').send({ message: 'Safe content' })
    expect(response.body.sanitizedBody).toEqual({ message: 'Safe content' })
  })

  test('Handles empty input gracefully', async () => {
    const response = await request(app).post('/submit').send({ emptyField: '' })
    expect(response.body.sanitizedBody).toEqual({ emptyField: '' })
  })
})
