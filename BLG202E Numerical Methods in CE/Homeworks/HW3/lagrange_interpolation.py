# Mustafa Can Caliskan
# 150200097

import numpy as np
from matplotlib import pyplot as plt

x_list = []
y_list = []

def lagrange(find):
    result = 0.0
    for x in range(0, len(x_list)):
        l_temp = 1.0
        for y in range(0, len(x_list)):
            if x != y:
                l_temp *= (find - x_list[y]) / (x_list[x] - x_list[y])
        result += l_temp * y_list[x]
    return result

def sketch(find):
    x = np.linspace(0, find + 2, num=10)
    plt.plot(x, lagrange(x), color="red", lw=2)
    plt.grid()
    plt.show()
    
x_input = input("Enter x values in the format x0, x1, x2,...: ")
x_input = x_input.replace(" ", "")
x_list = x_input.split(",")
x_list = list(np.float_(x_list))

y_input = input("Enter y values in the format y0, y1, y2,...: ")
y_input = y_input.replace(" ", "")
y_list = y_input.split(",")
y_list = list(np.float_(y_list))

find = float(input("Enter an a value to determine y at x = a: "))

print("\nUsing Lagrange Interpolation method, y at x = ", find, " is: ", lagrange(find), sep="")
sketch(find)