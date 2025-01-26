- init:
    run: rm -f combination
    blocker: true

- build:
    run: gcc -std=c99 -Werror combination.c -o combination  # timeout: 2
    blocker: true

- case1:
    run: ./combination
    points: 10
    script:
        - expect: "Enter n and r: "  # timeout: 2
        - send: "9 3"
        - expect: "84\r\n"  # timeout: 2
    exit: 0

- case2:
    run: ./combination
    points: 10
    script:
        - expect: "Enter n and r: "  # timeout: 2
        - send: "5 5"
        - expect: "1\r\n"  # timeout: 2
    exit: 0

- case3:
    run: ./combination
    points: 10
    script:
        - expect: "Enter n and r: "  # timeout: 2
        - send: "6 0"
        - expect: "1\r\n"  # timeout: 2
    exit: 0
