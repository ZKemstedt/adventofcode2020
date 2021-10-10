
class Instruction:
    def __init__(self, name: str, arg: str):
        self.name: str = name
        self.arg: int = int(arg)

    @classmethod
    def flipped(cls, obj):  # type ?
        if obj.name == 'nop':
            return Instruction('jmp', obj.arg)
        elif obj.name == 'jmp':
            return Instruction('nop', obj.arg)
        else:
            return obj


class Game:
    def __init__(self, instructions: list[Instruction]):
        self.instructions: list[Instruction] = instructions
        self.done: list[bool] = len(instructions) * [False]
        self.end: int = len(instructions)
        self._acc: int = 0
        self.line: int = 0

    def acc(self, arg: int) -> None:
        self.line += 1
        self._acc += arg

    def jmp(self, arg: int) -> None:
        self.line += arg

    def nop(self, arg: int) -> None:
        self.line += 1

    def run(self) -> bool:
        if self.line > self.end or self.line < 0:
            return 'error'

        if self.line == self.end:
            return 'done'

        if self.done[self.line]:
            return 'loop'

        self.done[self.line] = True
        ins = self.instructions[self.line]
        action = getattr(self, ins.name)

        if action:
            action(ins.arg)
            return 'ok'

        print(f'missed instruction: {ins.name} {ins.arg} line: {self.line}')

        return 'error'


def parse_line(line: str) -> Instruction:
    name, arg = line.split(' ')
    return Instruction(name, arg)


def main() -> None:
    with open('input.txt') as f:
        instructions = [parse_line(line) for line in f.readlines()]

    # Part 1
    game = Game(instructions)
    run = True
    while run:
        run = True if game.run() == 'ok' else False

    print(f'Part 1: {game._acc}')

    # Part 2
    solved = False
    for i, ins in enumerate(instructions):
        new = instructions[:i] + [Instruction.flipped(ins)] + instructions[i+1:]
        game = Game(new)

        while True:
            res = game.run()

            if res == 'ok':
                continue

            if res == 'done':
                solved = True

            if res in ['error', 'loop', 'done']:
                break

        if solved:
            print(f'Part 2: {game._acc}')
            break


if __name__ == '__main__':
    main()
