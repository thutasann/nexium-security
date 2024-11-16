// @ts-check
describe('Basic Math Operations', () => {
  test('adds 1 + 2 to equal 3', () => {
    expect(1 + 2).toBe(3)
  })

  test('basic math operations', () => {
    expect(2 * 3).toBe(6)
    expect(10 - 5).toBe(5)
    expect(15 / 3).toBe(5)
  })

  test('checking inequality', () => {
    expect(5).not.toBe(6)
  })
})

describe('Array Operations', () => {
  test('array contains specific item', () => {
    const shoppingList = ['milk', 'bread', 'eggs']
    expect(shoppingList).toContain('bread')
    expect(shoppingList).toHaveLength(3)
  })
})
