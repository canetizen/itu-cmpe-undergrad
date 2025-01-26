"""
    Mustafa Can Caliskan
    150200097
    BLG202E
    HW1
"""

import math

def converter(i_non_frac, i_frac):
    i_non_frac_binary = ""
    if i_non_frac == 0:
        i_non_frac_binary = "0"
    while i_non_frac / 2 != 0:
        i_non_frac_binary += str(i_non_frac % 2)
        i_non_frac = int(i_non_frac / 2)
    i_non_frac_binary = i_non_frac_binary[::-1]

    i_frac_binary = ""
    while i_frac % 1 != 0:
        if i_frac >= 1:
            i_frac = float(i_frac - 1)
        i_frac *= 2
        i_frac_binary += str(math.floor(i_frac))
    if i_frac_binary == "":
        return i_non_frac_binary
    else:
        return i_non_frac_binary + "." + i_frac_binary

def main():
    i = str(input("Enter a rational number in either x.yzt or x/y format: "))
    negative_flag = False
    if i[0] == '-':
        i = i[1:]
        negative_flag = True
    i_non_frac = 0
    i_frac = 0.0
    x = i.split("/")
    y = i.split(".")

    if len(x) != 1 and len(y) != 1:
        print("ERROR: Unsupported format.")
        return
    
    if len(x) != 1: # x/y
        if int(x[1]) == 0:
            print("ERROR: Input is not a rational number.")
            return
        i_non_frac = int(int(x[0]) / int(x[1]))
        i_frac = float((float(x[0]) / int(x[1])) % 1)

    elif len(y) != 1: # x.yzt
        i_non_frac = math.floor(float(x[0]))
        i_frac = float(float(i) - i_non_frac)
        
    print("The binary representation of given rational number is: ")
    if negative_flag:
        print("-" + converter(i_non_frac, i_frac))
    else:
        print(converter(i_non_frac, i_frac))
main()