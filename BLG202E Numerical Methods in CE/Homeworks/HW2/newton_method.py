##
# Mustafa Can Caliskan
# 150200097
##

import math

def f(x):
    return 4 * math.log(x, math.e) - x

def f_der(x):
    return 4 / x - 1

def newton_error_est(list, i_0):
    error_list = []
    error_list.append(abs(list[0] - i_0))
    for i in range(1, len(list)):
        error_list.append(abs(list[i] - list[i - 1]))
    return error_list

def secant_error_est(list, i_0, i_1):
    error_list = []
    error_list.append(abs(i_1 - i_0))
    error_list.append(abs(list[0] - i_1))
    for i in range(1, len(list)):
        error_list.append(abs(list[i] - list[i - 1]))
    return error_list

def newton(i_0, iter):
    newton_list = []
    i_current = i_0
    for x in range(1, iter + 1):
        i_func = f(i_current)
        i_der_func = f_der(i_current)
        result = i_current - i_func / i_der_func
        newton_list.append(result)
        i_current = result
    return newton_list

def secant(i_0, i_1, iter):
    secant_list = []
    i_current_prev = i_0
    i_current = i_1
    for x in range(2, iter + 2):
        i_func_prev = f(i_current_prev)
        i_func = f(i_current)
        result = i_current - (i_func * (i_current - i_current_prev)) / (i_func - i_func_prev)
        secant_list.append(result)
        i_current_prev = i_current
        i_current = result
    return secant_list

i_0 = float(input("Enter initial value x_0: "))
i_1 = float(input("Enter initial value x_1 (for secant method): "))
iter = int(input("Enter the number of maximum iteration: "))

print("")

print("######-Newton's Method-######")
newton_list = newton(i_0, iter)
i = 1
for x in newton_list:
    print("x_", i, " is:", x, sep='')
    i += 1

print("")

print("######-Newton's Method Error Estimation-######")
newton_error = newton_error_est(newton_list, i_0)
i = 1
for x in newton_error:
    print("Error estimation for x_", i - 1, " to x_", i, " is:", x, sep='')
    i += 1

print("")

print("######-Secant Method-######")
i = 2
secant_list = secant(i_0, i_1, iter)
for x in secant_list:
    print("x_", i, " is:", x, sep='')
    i += 1

print("")

print("######-Secant Method Error Estimation-######")
i = 1
secant_error = secant_error_est(secant_list, i_0, i_1)
for x in secant_error:
    print("Error estimation for x_", i - 1, " to x_", i, " is:", x, sep='')
    i += 1
