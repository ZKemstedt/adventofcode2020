import re

from collections.abc import Callable


shiny_gold = 'shiny gold'


def parse_rule(line: str) -> tuple[str, dict[str, int]]:
    parts = line.split(' bags contain ')
    color = parts[0]
    result = re.findall(r'(\d+) (.*?) (bag)', parts[1])
    content = [(g[1], int(g[0])) for g in result]
    return (color, dict(content))


# p1
def can_contain_shiny_gold(rules: dict[str, dict[str, int]]) -> Callable[str]:
    def rec(color: str) -> bool:
        content = rules[color]
        return shiny_gold in content or any(rec(color) for color in content)
    
    return rec


def how_many_bags_can_contain_shiny_gold(rules: dict[str, dict[str, int]]) -> int:
    return countif(can_contain_shiny_gold(rules), rules.keys())


def countif(fn: Callable, lst: list) -> int:
    return len([x for x in lst if fn(x)])


# p2
def count_contents_and_self(rules: dict[str, dict[str, int]]) -> Callable[str]:
    def rec(color: str) -> int:
        contents = rules[color]
        self = 1
        return self + sum([rec(color) * count for (color, count) in contents.items()])

    return rec


def how_many_bags_required_inside_shiny_gold(rules: dict[str, dict[str, int]]) -> int:
    return count_contents_and_self(rules)(shiny_gold) - 1


def main():
    with open('input.txt') as f:
        rules = dict([parse_rule(rule) for rule in f.readlines()])
    print(how_many_bags_can_contain_shiny_gold(rules))
    print(how_many_bags_required_inside_shiny_gold(rules))


if __name__ == '__main__':
    main()

