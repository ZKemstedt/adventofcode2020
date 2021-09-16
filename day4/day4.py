# NOTE
# Part 1 works
# Part 2 is broken, no ETA for fix


class Passport:
    def __init__(self, **kwargs):
        self.pid = kwargs.get('pid')
        self.hcl = kwargs.get('hcl')
        self.byr = kwargs.get('byr')
        self.iyr = kwargs.get('iyr')
        self.eyr = kwargs.get('eyr')
        self.cid = kwargs.get('cid')
        self.hgt = kwargs.get('hgt')
        self.ecl = kwargs.get('ecl')

    def __str__(self) -> str:
        return (f"hcl: {self.hcl} pid: {self.pid}"
                f"hcl: {self.hcl} byr: {self.byr}"
                f"iyr: {self.iyr} eyr: {self.eyr}"
                f"cid: {self.cid} hgt: {self.hgt}"
                f"ecl: {self.ecl}")

    def is_valid(self) -> bool:
        """Part 1
        Passports are valid when all fields (ignoring cid) are set
        """
        return all([self.hcl, self.byr, self.iyr, self.eyr, self.pid, self.hgt, self.ecl])

    def is_valid2(self) -> bool:
        """Part 2
        Passports are valid when...
            byr is at least 1920 and at most 2002.
            iyr is at least 2010 and at most 2020.
            eyr is at least 2020 and at most 2030.
            hgt is a number followed by either cm or in:
                If cm, the number must be at least 150 and at most 193.
                If in, the number must be at least 59 and at most 76.
            hcl is a # followed by exactly six characters 0-9 or a-f.
            ecl is exactly one of: amb blu brn gry grn hzl oth.
            pid is a nine-digit number, including leading zeroes.
        """
        if not self.is_valid():
            return False

        if (int(self.byr) > 2002):
            invalid("byr", f"{self.byr} > 2002")
        elif int(self.byr) < 1920:
            invalid("byr", f"{self.byr} < 1920")
        elif int(self.iyr) > 2020:
            invalid("iyr", f"{self.iyr} > 2020")
        elif int(self.iyr) < 2010:
            invalid("iyr", f"{self.iyr} < 2010")
        elif int(self.eyr) > 2030:
            invalid("eyr", f"{self.eyr} > 2030")
        elif int(self.eyr) < 2020:
            invalid("eyr", f"{self.eyr} < 2020")

        if self.hgt[-2:] == "cm":
            if int(self.hgt[:-2]) < 150:
                invalid("hgt-cm", f"{self.hgt[:-2]} < 150")
            elif int(self.hgt) > 193:
                invalid("hgt-cm", f"{self.hgt[:-2]} > 193")
        elif self.hgt[-2:] == "in":
            if int(self.hgt[:-2]) < 59:
                invalid("hgt-in", f"{self.hgt[:-2]} < 59")
            elif int(self.hgt) > 76:
                invalid("hgt-in", f"{self.hgt[:-2]} > 76")

        checks = [
            (int(self.byr) < 1920, (int(self.byr) > 2002), (int(self.iyr) < 2010), (int(self.iyr) > 2020),
            (int(self.eyr) < 2020), (int(self.eyr) > 2030), (int(self.iyr) < ))
            # (
            #     ("cm" == self.hgt[-2:] and 150 <= int(self.hgt[:-2]) <= 193)
            #     or ("in" == self.hgt[-2:] and 59 <= int(self.hgt[:-2]) <= 76)
            # ),
            # (self.hcl[0] == "#" and all([c in "0123456789abcdef" for c in self.hcl[1:]])),
            # (self.ecl in ["amb", "blu", "brn", "gry", "grn", "hzal", "oth"]),
            # (len(self.pid) == 9 and self.pid.isnumeric())
        ]
        return all(checks)

    def hgt_check(self) -> bool:
        return (
            ("cm" == self.hgt[-2:] and 150 <= int(self.hgt[:-2]) <= 193) or
            ("in" == self.hgt[-2:] and 59 <= int(self.hgt[:-2]) <= 76)
        )


def invalid(field: str, text: str) -> None:
    print(f"invalid {field}: {text}")


def parse_passports(fields: list[str]) -> list[Passport]:
    passports = []
    args = []
    for field in fields:
        if field:
            args.append(field)
        if not field:
            kwargs = dict([arg.split(':') for arg in args])
            passports.append(Passport(**kwargs))
            args = []

    return passports


def main() -> None:
    with open('input.txt') as f:
        fields = f.read().replace(' ', '\n').split('\n')

    passports = parse_passports(fields)
    print(f"found {len(passports)} passports")
    valid_passports = len([passport for passport in passports if passport.is_valid()])
    valid_passports2 = len([passport for passport in passports if passport.is_valid2()])
    # for passport in passports:
    #     print(passport)
    print(f"valid passwords: {valid_passports}")
    print(f"valid passwords2: {valid_passports2}")


if __name__ == "__main__":
    main()
