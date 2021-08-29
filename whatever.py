
# other than __init__ there are a bunch of other special properties, examples include
# __len__ __iter__ __next__ __eq__ __str__ __repr__ __gt__ __lt__

# Using our own implementations of a *list of numbers* and *number*,
# we will iterate (loop) through the list and compare some numbers to each others

class NumberList:

    def __init__(self):
        self.numbers = []

    def addNumber(self, number):
        self.numbers.append(number)

    def __str__(self): # if you print or convert this object into a string, this is the value that will be used, must return a string
        return " ".join(str(number) for number in self.numbers)

    def __repr__(self): # somewhat similar to __str__, this is the string *representation* of the object, so it must also return a string
        return "NumerList[Number]"

    def __len__(self): # enables using len() on the object, this method must return a number
        return len(self.numbers)

    def __iter__(self):
        self.index = -1 # reset the index
        return self

    def __next__(self):
        self.index = self.index + 1
        if self.index == len(self): # this calls the __len__ method we defined above
            raise StopIteration
        return self.numbers[self.index]
      

class Number:
  
    def __init__(self, value):
        self.value = value

    def __str__(self):
        return str(self.value)
  
    def __eq__(self, number):  # enables logical equals eg. ´Number(1) == Number(2)´ will return True
        return self.value == number.value

    def __lt__(self, number): # logical less than
        return self.value < number.value

    def __gt__(self, number): # logical greater than
        return self.value > number.value

numbers = NumberList() # Instanciate the list and save it to numbers, numbers is now a NumberList object

number = Number(1) # a number object
numbers.addNumber(number) # add this number object into our list

# Instead of saving the number object to a variable and then sending the variable to numbers.addNumber()
# we can just send the object directly
numbers.addNumber(Number(2))

numbers.addNumber(Number(3))
numbers.addNumber(Number(5))
numbers.addNumber(Number(2))
numbers.addNumber(Number(5))
numbers.addNumber(Number(5))
numbers.addNumber(Number(4))

# ok, now let's do some iteration (aka looping)

print("\nSome ways to print our numbers")

# manually looping through NumberList, this uses NumberList.__iter__()
for number in numbers:
    print(number)

# this does the same thing as above
print(" ".join(str(number) for number in numbers))

print(numbers) # using NumberList.__str__()

# for comparisons we will keep track of the previous number throughout the iteration
prev = None
for number in numbers:
    if prev:
        if prev == number:
            print(prev, "==", number)
        elif prev > number:
            print(prev, ">", number)
        elif prev < number:
            print(prev, "<", number)
    prev = number
    