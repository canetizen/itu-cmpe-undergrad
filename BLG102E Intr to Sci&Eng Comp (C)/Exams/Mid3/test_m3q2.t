- init:
    run: rm -f m3q2
    blocker: true

- build:
    run: gcc -std=c99 -Wall -Werror m3q2.c -o m3q2  # timeout: 2
    blocker: true

- case1:
    run: ./m3q2
    points: 1
    script:
        - expect: "n, a, b, seed: "  # timeout: 2
        - send: "5 1 6 10"
        - expect: "2 5 3 6 1\r\n"  # timeout: 2
    exit: 0