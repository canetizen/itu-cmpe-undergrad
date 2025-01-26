- init:
    run: rm -f digits
    blocker: true

- build:
    run: gcc -std=c99 -Wall -Werror digits.c -o digits  # timeout: 2
    blocker: true

- case_147:
    run: ./digits
    points: 10
    script:
        - expect: "Enter a 3 digit number:"  # timeout: 2
        - send: "147"
        - expect: "Digits of number 147 are 1, 4, 7 respectively\r\n"                   # timeout: 2
        - expect: _EOF_  # timeout: 2
    exit: 0

- case_739:
    run: ./digits
    points: 10
    script:
        - expect: "Enter a 3 digit number:"  # timeout: 2
        - send: "739"
        - expect: "Digits of number 739 are 7, 3, 9 respectively\r\n"                   # timeout: 2
        - expect: _EOF_  # timeout: 2
    exit: 0