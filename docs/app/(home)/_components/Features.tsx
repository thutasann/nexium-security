import React from 'react'

function Features() {
  return (
    <div className="grid grid-cols-1 md:grid-cols-3 gap-6 mt-24">
      <div className="p-6 rounded-lg bg-gradient-to-br from-purple-500/10 to-blue-500/10 border border-purple-500/20 shadow-sm hover:shadow-md transition-shadow">
        <h3 className="font-semibold mb-2 text-purple-700 dark:text-purple-300">Native C Performance</h3>
        <p className="text-muted-foreground">
          Built entirely in C for maximum performance and low-level system access, providing robust security primitives.
        </p>
      </div>

      <div className="p-6 rounded-lg bg-gradient-to-br from-blue-500/10 to-cyan-500/10 border border-blue-500/20 shadow-sm hover:shadow-md transition-shadow">
        <h3 className="font-semibold mb-2 text-blue-700 dark:text-blue-300">Memory-Safe Operations</h3>
        <p className="text-muted-foreground">
          Carefully designed with secure memory management and bounds checking to prevent common security
          vulnerabilities.
        </p>
      </div>

      <div className="p-6 rounded-lg bg-gradient-to-br from-cyan-500/10 to-purple-500/10 border border-cyan-500/20 shadow-sm hover:shadow-md transition-shadow">
        <h3 className="font-semibold mb-2 text-cyan-700 dark:text-cyan-300">Cryptographic Primitives</h3>
        <p className="text-muted-foreground">
          Access to low-level cryptographic functions and secure random number generation for building trusted
          applications.
        </p>
      </div>
    </div>
  )
}

export default Features
