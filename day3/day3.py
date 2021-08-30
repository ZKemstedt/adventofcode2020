ROWLEN = 31  # 32 but we don't want the newline


def read_input_file(day: str) -> list[str]:
    with open(f"{day}/input.txt") as f:
        lines = f.readlines()
    return lines


def split(word: str) -> list[str]:
    word = word[:ROWLEN]
    return [char for char in word]


def traverse_matrix(matrix: list[list[str]], move_x: int, move_y: int) -> int:
    goal = len(matrix)  # 323
    x, y, trees = 0, 0, 0

    while y < goal:
        if x >= ROWLEN:
            x -= ROWLEN

        if matrix[y][x] == '#':
            trees += 1

        y += move_y
        x += move_x

    return trees


def run() -> None:
    lines = read_input_file('day3')
    matrix = [split(line) for line in lines]
    lanes = [
        (1, 1),
        (3, 1),
        (5, 1),
        (7, 1),
        (1, 2)
    ]
    product = 1
    for i, lane in enumerate(lanes, start=1):
        res = traverse_matrix(matrix, lane[0], lane[1])
        print(f'lane {i} (right {lane[0]}, down {lane[1]}) encountered {res} trees.')
        product *= res
    print(f'product of all trees encountered: {product}')

def traverse_v2(right: int, down: int) -> int:
    pass

def v2() -> None:
    with open(f"day3/input.txt") as f:
        lines = [line[:31] for line in f.readlines()]


if __name__ == "__main__":
    run()
