from functools import reduce


def travel(matrix, right: int, down: int) -> int:
    width = len(matrix[0].strip())
    trees = len([
        x for x, line
        in enumerate(matrix[::down])
        if line[(x * right) % width] == "#"
    ])
    return trees


def run() -> None:
    with open("day3/input.txt") as f:
        lines = f.readlines()
    right = [1, 3, 5, 7, 1]
    down = [1, 1, 1, 1, 2]
    trees = [
        travel(lines, right[i], down[i])
        for i
        in range(5)
    ]
    print("\n".join([
        f"Lane {i + 1}: {tree} trees"
        for i, tree
        in enumerate(trees)
    ]))

    p = reduce(lambda x, y: x * y, trees)
    print(f"\n\tThe product of encountered trees of each lane is: {p}\n")


if __name__ == "__main__":
    run()
