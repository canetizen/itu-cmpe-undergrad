"""
    Mustafa Can Caliskan
    150200097
    BLG202E
    HW1
"""

import math

def func(x, a):
    return (x**5 - a)

def bisection(lower, upper, a, e):
    x = (lower + upper) / 2
    if e != 0:
        n_max_iteration = math.ceil(math.log(abs(upper - lower) / (2 * e), 2))
    else:
        n_max_iteration = 100000
    while abs(func(x, a)) > e and n_max_iteration:
        if func(x, a) < 0:
            lower = x
        else:
            upper = x
        x = (upper + lower) / 2
        n_max_iteration -= 1
    return x

def main():
    a = float(input("Enter a: "))
    e = float(input ("Enter e: "))
    lower = -a
    upper = a
    result = bisection(lower, upper, a, e)
    print("The approximation is: ")
    print(result)
    print("Absolute Error: ")
    print(abs(pow(a, 1/5) - result))
main()