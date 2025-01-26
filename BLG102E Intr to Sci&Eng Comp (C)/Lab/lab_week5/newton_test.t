- init:
    run: rm -f newton_method
    blocker: true

- build:
    run: gcc -std=c99 -Werror newton_method.c -lm -o newton_method  # timeout: 2
    blocker: true

- case_1:
    run: ./newton_method
    points: 1
    script:
        - send: "1 -2 -15"
        - expect: "Root: 5.00\r\n"  # timeout: 2
    exit: 0

- case_2:
    run: ./newton_method
    points: 1
    script:
        - send: "1 -2 -20"
        - expect: "Root: 5.58\r\n"  # timeout: 2
    exit: 0

- case_3:
    run: ./newton_method
    points: 1
    script:
        - send: "2 -11.53 -24.8"
        - expect: "Root: 7.43\r\n"  # timeout: 2
    exit: 0
