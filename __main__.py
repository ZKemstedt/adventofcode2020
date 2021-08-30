from cmd import Cmd

class Menu(Cmd):
    intro = 'Advent of Code 2020, solutions by Zephyro\n    Type help or ? to list commands.\n'
    prompt = '>>'

    def do_day1(self, line):
        import day1.day1
        day1.run()

    def do_day2(self, line):
        pass

    def do_day3(self, line):
        pass

    def do_exit(self, line):
        pass
    
    def precmd(self, line):
        line = line.lower()

if __name__ == '__main__':
    Menu().cmdloop()