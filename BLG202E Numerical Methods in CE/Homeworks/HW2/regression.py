##
# Mustafa Can Caliskan
# 150200097
##

from matplotlib import pyplot as plt
import numpy as np

data = ['0.5, 0.72,', '1, 1.63,', '1.5, 1.88,',
            '2, 3.39,', '2.5, 4.02,', '3, 3.89,',
            '3.5, 4.25,', '4, 3.99,', '4.5, 4.68,',
            '5, 5.03,', '5.5, 5.27', '6, 4.82,',
            '6.5, 5.67,', '7, 5.95,', '7.5, 5.72,',
            '8, 6.01,,', '8.5, 5.5,', '9, 6.41,', 
            '9.5, 5.83,', '10, 6.33,'
            ]

x = [float(i.split(',')[0]) for i in data]
y = [float(i.split(',')[1]) for i in data]

###Data
plt.xlim(0, 11)
plt.ylim(0, 8)
plt.scatter(x, y, marker='o')

###Line
b, a = np.polyfit(x, y, deg=1)
xseq = np.linspace(0, 11, num=1000)
plt.plot(xseq, a + b * xseq, color="black", lw=2, label='Line')
print("l(x) = ", a, " + ", b, "x", sep='')

###2nd Order Polynomial
c, d, e = np.polyfit(x, y, deg=2)
plt.plot(xseq, e + d * xseq + c * xseq * xseq, color="red", lw=2, label='2nd Order Polynomial')
print("p(x) = ", e, " + ", d, "x", " + ", c, "x^2", sep='')

###Logarithmic
xseq2 = np.linspace(0.01, 11, num=1000)
m, k = np.polyfit(np.log(x), y, 1)
plt.plot(xseq2, k + m * np.log(xseq2), color="orange", lw=2, label='Logarithmic')
print("f(x) = ", k, " + ", m, "ln(x)", sep='')

plt.xlabel('x_i')
plt.ylabel('y_i')
plt.legend()
plt.grid()
plt.show()