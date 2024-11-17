// @ts-check
const express = require('express')
const bodyParser = require('body-parser')
const { NMiddleware } = require('../lib')

/** express app for testing purpose */
const app = express()

// middlewares
app.use(bodyParser.json())
app.use(NMiddleware.sanitizeInput)

// testing routes
app.post('/submit', (req, res) => {
  res.json({ sanitizedBody: req.body })
})

module.exports = app
