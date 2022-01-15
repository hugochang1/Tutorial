import pyinputplus

r = None

# same as input()
# r = pyinputplus.inputStr("please input a String: ")
# r = pyinputplus.inputStr("please input a String: ", blank=True)
# r = pyinputplus.inputStr("please input a String: ", blockRegexes=[r'(A|B|C)'])
"""
try:
    r = pyinputplus.inputStr("please input a String: ", limit=2, default="N/A")
except Exception as err:
    print(err)
"""

# r = pyinputplus.inputNum("please input a number (integer + float): ")
# r = pyinputplus.inputNum("please input: ", allowRegexes=[r'(A|B|C)', r'zero'])


# r = pyinputplus.inputInt("please input a integer: ")
# r = pyinputplus.inputInt("please input a integer: ", min=3, max=8)
# r = pyinputplus.inputInt("please input a integer: ", greaterThan=3, lessThan=8)

# r = pyinputplus.inputYesNo("please input a Yes or No: ")

# r = pyinputplus.inputBool("please input a True or False: ")

# r = pyinputplus.inputEmail("please input a e-mail: ")

# r = pyinputplus.inputFilepath("please input a file path: ")

# r = pyinputplus.inputPassword("please input a password: ")

"""
def my_fun(user_input):
    print("my_fun() user_input=", user_input)
    return 123

r = pyinputplus.inputCustom(my_fun, "plesae input something: ")
"""

your_choice = ["a", "b", "c"]

# r = pyinputplus.inputChoice(your_choice)
"""
Please select one of: a, b, c
"""

# r = pyinputplus.inputMenu(your_choice, numbered=True)
"""
Please select one of the following:
1. a
2. b
3. c
"""

# r = pyinputplus.inputDate("please input a date: ")
# please input a date: 199/1/1
# <class 'datetime.date'> 1999-01-01

print(type(r), r)
