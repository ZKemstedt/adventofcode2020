import re

# explanation: https://regex101.com/r/s6K4gQ/1/
reg = r'[0-9]+|[0-9]+|[a-z]{1}(?=:)|[a-z]+$'

def check1(line):
    sizemin, sizemax, key, password = re.findall(reg, line)
    return int(sizemin) <= password.count(key) <= int(sizemax)

def check2(line):
    pos1, pos2, key, password = re.findall(reg, line)
    pattern = build_pattern(int(pos1)-1, int(pos2)-1, key)
    return bool(pattern.match(password))

def build_pattern(i, j, key):
    string = "^"                                    # start of string
    if i != 0:
        string += f".{{{i}}}"                       # ignore irrelevant chars
    string += f"(?:{key}{{1}}"                      # if pos1 has key
    string += f"(?!.{{{j-i-1}}}{key}{{{1}}})"       # and pos2 does not
    string += f"|[^{key}]{{1}}"                     # or pos1 no key
    string += f"(?=.{{{j-i-1}}}{key}{{{1}}}))"      # and pos2 does

    pattern = re.compile(string)
    return pattern


def run(check):
    with open("day2/input.txt", "r") as f:
        valid_count = len([line for line in f.readlines() if check(line)])

    print(f"Found {valid_count} valid passwords.")


if __name__ == '__main__':
    run(check1)
    run(check2)
