// @ts-check
const express = require('express')
const bodyParser = require('body-parser')
const { NMiddleware } = require('../lib')
const { IPS, DOMAINS } = require('./utils/constants')

/** express app for testing purpose */
const app = express()

// middlewares
app.use(bodyParser.json())
app.use(NMiddleware.sanitizeInput)
NMiddleware.setupFilters(IPS, DOMAINS)
app.use(NMiddleware.filterRequest)
app.use(NMiddleware.headerInspection)
// app.use(NMiddleware.csrfMiddleware('dynamic-secret-key'))

app.get('/', (req, res) => {
  res.send('Hello, World!')
})

// testing routes
app.post('/submit', (req, res) => {
  res.json({ sanitizedBody: req.body })
})

// app.listen(3000, () => {
//   console.log(`Express app is listening on http://localhost:${3000} ✅`)
// })

module.exports = app
