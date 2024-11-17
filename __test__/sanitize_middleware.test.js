// @ts-check
const request = require('supertest')
const app = require('../express/app')

describe('Sanitize Middleware', () => {
  test('Sanitizes and escapes dangerous characters', async () => {
    const response = await request(app)
      .post('/submit')
      .send({ name: '<script>alert("xss")</script>', comment: 'Hello & Goodbye' })

    expect(response.body.sanitizedBody).toEqual({
      name: '&lt;script&gt;alert(&quot;xss&quot;)&lt;\\/script&gt;',
      comment: 'Hello &amp; Goodbye',
    })
  })

  test('Sanitizes and escapes SQL injection attempts', async () => {
    const response = await request(app).post('/submit').send({
      username: "admin'; DROP TABLE users; --",
      query: "SELECT * FROM users WHERE name LIKE '%admin%'",
    })

    expect(response.body.sanitizedBody).toEqual({
      username: 'admin&#39;\\; DROP TABLE users\\; \\-\\-',
      query: 'SELECT * FROM users WHERE name LIKE &#39;\\%admin\\%&#39;',
    })
  })

  test('Sanitizes NoSQL injection attempts', async () => {
    const response = await request(app).post('/submit').send({
      username: '{"$gt": ""}',
      password: '{"$ne": null}',
      query: '{"$where": "function() { return true }"}',
      filter: '{"$regex": ".*"}',
      malicious: '{"$function": {"body": "while(true){}"}}',
      search: 'admin", "$or": [{"":"',
    })
    expect(response.body.sanitizedBody).toEqual({
      username: '{&quot;$gt&quot;: &quot;&quot;}',
      password: '{&quot;$ne&quot;: null}',
      query: '{&quot;$where&quot;: &quot;function() { return true }&quot;}',
      filter: '{&quot;$regex&quot;: &quot;.*&quot;}',
      malicious: '{&quot;$function&quot;: {&quot;body&quot;: &quot;while(true){}&quot;}}',
      search: 'admin&quot;, &quot;$or&quot;: [{&quot;&quot;:&quot;',
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
