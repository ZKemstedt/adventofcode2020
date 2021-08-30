
with open("day1/input.txt", "r") as f:
    numbers = [int(num) for num in f.readlines()]

# # Part 1
# # Find the two entries that sum to 2020 and then multiply those two numbers together.
def part1(numbers):
    return [num*(2020-num) for num in numbers if 2020-num in numbers].pop()

# # Part 2
# # Find the three entries that sum to 2020 and then multiply those two numbers together.
def part2(numbers):
    # nested list comprehensions are not easy on the eyes...
    for num1 in numbers:
        for num2 in numbers:
            if 2020-num1-num2 in numbers:
                return num1*num2*(2020-num1-num2)

print(part1(numbers))
print(part2(numbers))
