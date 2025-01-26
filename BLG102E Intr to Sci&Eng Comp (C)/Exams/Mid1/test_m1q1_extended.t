- init:
    run: rm -f m1q1
    blocker: true

- build:
    run: gcc -std=c99 -Wall -Werror m1q1.c -o m1q1  # timeout: 2
    blocker: true

- case1:
    run: ./m1q1
    points: 5
    script:
        - expect: "Give three integers separated with space:"  # timeout: 2
        - send: "3 6 9"
        - expect: "strictly increasing\r\n"  # timeout: 2
    exit: 0

- case2:
    run: ./m1q1
    points: 5
    script:
        - expect: "Give three integers separated with space:"  # timeout: 2
        - send: "9 6 3"
        - expect: "strictly decreasing\r\n"  # timeout: 2
    exit: 0

- case3:
    run: ./m1q1
    points: 10
    script:
        - expect: "Give three integers separated with space:"  # timeout: 2
        - send: "7 6 7"
        - expect: "none of the two\r\n"  # timeout: 2
    exit: 0


