// @ts-check

/**
 * Benchmarks a function by executing it multiple times and calculating the average execution time.
 * @param {Function} fn - The function to benchmark.
 * @param {Array<any>} args - The arguments to pass to the function.
 * @param {number} [runs=1000] - The number of times to execute the function for the benchmark.
 * @returns {number | any} - The average execution time in milliseconds.
 */
function benchmark_args(fn, args, runs = 1000, logResult = false) {
  // Warm-up runs to stabilize any JIT effects
  for (let i = 0; i < Math.min(10, runs); i++) {
    try {
      fn(...args)
    } catch (error) {
      console.error('Error during warm-up:', error)
      return null
    }
  }

  let totalDuration = 0n

  for (let i = 0; i < runs; i++) {
    const start = process.hrtime.bigint()
    try {
      fn(...args)
    } catch (error) {
      console.error('Error during benchmarking:', error)
      return null
    }
    const end = process.hrtime.bigint()
    totalDuration += end - start
  }

  const averageDuration = Number(totalDuration / BigInt(runs)) / 1e6 // Convert to milliseconds

  if (logResult) {
    console.log(`Average execution time for ${fn.toString()} over ${runs} runs: ${averageDuration.toFixed(4)} ms`)
  }

  return averageDuration
}

module.exports = {
  benchmark_args,
}
