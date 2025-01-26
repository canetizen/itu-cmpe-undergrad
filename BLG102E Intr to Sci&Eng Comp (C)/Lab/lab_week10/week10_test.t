- init:
    run: rm -f array
    blocker: true

- build:
    run: gcc -std=c99 -Wall -Werror reversed_array.c -o array  # timeout: 2
    blocker: true

- case_1:
    run: ./array
    points: 1
    script:
        - expect: "ORIGINAL ARRAY: 3    6    7    5    2    9    1    0    8    4"
        - expect: "REVERSE ARRAY:  4    8    0    1    9    2    5    7    6    3"
        - expect: _EOF_  # timeout: 2
    exit: 0
