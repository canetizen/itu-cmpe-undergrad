- init:
    run: rm -f m3q1
    blocker: true

- build:
    run: gcc -std=c99 -Wall -Werror m3q1.c -o m3q1  # timeout: 2
    blocker: true

- case1:
    run: ./m3q1
    points: 1
    script:
        - expect: "enter the string: "  # timeout: 2
        - send: "  dennis ritchie    "
        - expect: "enter the trim type \\(l, r, b\\)\\: "  # timeout: 2
        - send: "l"
        - expect: "\\|dennis ritchie    \\|\r\n"  # timeout: 2   
    exit: 0

- case2:
    run: ./m3q1
    points: 1
    script:
        - expect: "enter the string: "  # timeout: 2
        - send: "  dennis ritchie    "
        - expect: "enter the trim type \\(l, r, b\\)\\: "  # timeout: 2
        - send: "r"
        - expect: "\\|  dennis ritchie\\|\r\n"  # timeout: 2     
    exit: 0

- case3:
    run: ./m3q1
    points: 1
    script:
        - expect: "enter the string: "  # timeout: 2
        - send: "  dennis ritchie    "
        - expect: "enter the trim type \\(l, r, b\\)\\: "  # timeout: 2
        - send: "b"
        - expect: "\\|dennis ritchie\\|\r\n"  # timeout: 2        
    exit: 0