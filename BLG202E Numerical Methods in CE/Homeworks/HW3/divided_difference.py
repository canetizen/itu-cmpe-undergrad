# Mustafa Can Caliskan
# 150200097

import numpy as np
from matplotlib import pyplot as plt

def divided_difference(x_list, y_list, find):
    result = 0.0
    y_list_temp = y_list
    coefficients_list = []
    coefficients_list.append(y_list_temp[0])
    for i in range(1, len(x_list)):
        for j in range (len(x_list) - i):
            if len(y_list_temp) == 1:
                break
            temp_0 = y_list_temp[0]
            temp_1 = y_list_temp[1]
            result = (temp_1 - temp_0) / (x_list[i + j] - x_list[j])
            coefficients_list.append(result)
            y_list_temp.append(result)
            y_list_temp.pop(0)
        y_list_temp.pop(0)
    
    result = coefficients_list[0]
    s = 1
    increment = len(x_list) - 1
    for x in range(1, len(x_list)):
        prod_temp = 1.0
        for y in range(x):
            prod_temp *= (find - x_list[y])
        result += (prod_temp * coefficients_list[s])
        s += increment
        increment -= 1
    return result

def sketch(x_list, y_list, find):
    x = np.linspace(0, find + 2, num=10)
    plt.plot(x, divided_difference(x_list, y_list, x), color="red", lw=2)
    plt.grid()
    plt.show()
    
x_list = []
y_list = []

x_input = input("Enter x values in the format x0, x1, x2,...: ")
x_input = x_input.replace(" ", "")
x_list = x_input.split(",")
x_list = list(np.float_(x_list))

y_input = input("Enter y values in the format y0, y1, y2,...: ")
y_input = y_input.replace(" ", "")
y_list = y_input.split(",")
y_list = list(np.float_(y_list))

y_list_temp = y_list.copy()

find = float(input("Enter an a value to determine y at x = a: "))

print("\nUsing Divided Difference method, y at x = ", find, " is: ", divided_difference(x_list, y_list, find), sep="")
sketch(x_list, y_list_temp, find)



