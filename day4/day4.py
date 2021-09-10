
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
        return all([self.hcl, self.byr, self.iyr, self.eyr, self.pid, self.hgt, self.ecl])


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
    # for passport in passports:
    #     print(passport)
    print(f"valid passwords: {valid_passports}")


if __name__ == "__main__":
    main()
