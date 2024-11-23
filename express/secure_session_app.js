// @ts-check
const express = require('express')
const cookieParser = require('cookie-parser')
// @ts-ignore
// const { validateSession, generateSessionId, storeSession } = require('../build/Release/nexium-security.node')
const { NMiddleware } = require('../lib')

/** express app for testing purpose */
const secure_session_app = express()

// middlewares
secure_session_app.use(cookieParser())
secure_session_app.use(NMiddleware.secure_session)

secure_session_app.get('/', (req, res) => {
  res.send('Session is valid.')
})

// secure_session_app.listen(3000, () => {
//   console.log(`Express app is listening on http://localhost:${3000} ✅`)
// })

module.exports = secure_session_app
