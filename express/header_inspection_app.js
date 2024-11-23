// @ts-check
const express = require('express')
const bodyParser = require('body-parser')
const { NMiddleware } = require('../lib')

/** express app for testing purpose */
const header_inspection_app = express()

// middlewares
header_inspection_app.use(bodyParser.json())
header_inspection_app.use(NMiddleware.headerInspection)

header_inspection_app.get('/', (req, res) => {
  res.send('Hello, World!')
})

// testing routes
header_inspection_app.post('/submit', (req, res) => {
  res.json({ sanitizedBody: req.body })
})

// app.listen(3000, () => {
//   console.log(`Express app is listening on http://localhost:${3000} ✅`)
// })

module.exports = header_inspection_app
