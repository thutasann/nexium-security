// @ts-check
const express = require('express')
const bodyParser = require('body-parser')
const { NMiddleware } = require('../lib')
const { IPS, DOMAINS } = require('./utils/constants')

/** express app for testing purpose */
const sanitize_app = express()

// middlewares
sanitize_app.use(bodyParser.json())
sanitize_app.use(NMiddleware.sanitizeInput)

sanitize_app.get('/', (req, res) => {
  res.send('Hello, World!')
})

// testing routes
sanitize_app.post('/submit', (req, res) => {
  res.json({ sanitizedBody: req.body })
})

// app.listen(3000, () => {
//   console.log(`Express app is listening on http://localhost:${3000} ✅`)
// })

module.exports = sanitize_app
