import sys
sys.setrecursionlimit(1500)

text = """
35
20
15
25
47
40
62
55
65
95
102
117
150
182
127
219
299
277
309
576
""".strip().splitlines()

numbers = [int (x) for x in text]
preambleSize = 5

#  [35, 20, 15, 25, 47, 40, 62, 55, 65, 95, 102, 117, 150, 182, 127, 219, 299, 277, 309, 576]


def findInvalidValue(preamble: list[int], remaining: list[int]) -> int:
  if not remaining:
      return 0
  elif isValid(preamble, remaining[0]):
      return findInvalidValue(preamble[1:] + [remaining[0]], remaining[1:])
  else:
      return remaining[0]


def isValid(preamble: list[int], value: int) -> bool:
    return any(x + x != value and value - x in preamble for x in preamble)


def findWeakness(target: int, remaining: list[int]) -> list[int]:
    values = numbersThatStartsSumTo(target, remaining, [])

    if values:
        return values
    else:
        return findWeakness(target, remaining[1:])


def numbersThatStartsSumTo(target: int, remaining: list[int], soFar: list[int]) -> list[int]:
    if not remaining:
        return []

    head = remaining[0]
    tail = remaining[1:]

    if head == target:
        return soFar + [head]

    return numbersThatStartsSumTo(target - head, tail, soFar + [head])


def main():
    invalidValue = findInvalidValue( numbers[:preambleSize], numbers[preambleSize:] )
    print(f"Part 1: {invalidValue}")

    weakness = findWeakness(invalidValue, numbers)
    print(f"Part 2: {max(weakness) + min(weakness)}")


main()