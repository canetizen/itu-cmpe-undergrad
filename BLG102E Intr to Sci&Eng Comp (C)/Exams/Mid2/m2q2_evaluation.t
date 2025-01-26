- init:
    run: rm -f m2q2
    blocker: true

- build:
    run: gcc -std=c99 -Wall -Werror m2q2.c -o q2  # timeout: 2
    blocker: true

- case1:
    run: ./q2
    points: 5
    script:
        - expect: "Enter up to 10 non-negative integers \\(-1 to terminate\\)\\:"  # timeout: 2
        - send: "2 3 4 5 6 2 3 4 4 5"
        - expect: "\r\nEnter your choice \\(1 for alternating sum or 2 for alternating division\\)\\:"  # timeout: 2
        - send: "1"
        - expect: "The result is 0.00\r\n"  # timeout: 2
    exit: 0

- case2:
    run: ./q2
    points: 5
    script:
        - expect: "Enter up to 10 non-negative integers \\(-1 to terminate\\)\\:"  # timeout: 2
        - send: "2 3 4 5 6 2 3 4 4 5"
        - expect: "\r\nEnter your choice \\(1 for alternating sum or 2 for alternating division\\)\\:"  # timeout: 2
        - send: "2"
        - expect: "The result is 0.96\r\n"  # timeout: 2
    exit: 0

- case3:
    run: ./q2
    points: 5
    script:
        - expect: "Enter up to 10 non-negative integers \\(-1 to terminate\\)\\:"  # timeout: 2
        - send: "2 3 4 5 6 7 8 9 10 11"
        - expect: "\r\nEnter your choice \\(1 for alternating sum or 2 for alternating division\\)\\:"  # timeout: 2
        - send: "1"
        - expect: "The result is -5.00\r\n"  # timeout: 2
    exit: 0

- case4:
    run: ./q2
    points: 5
    script:
        - expect: "Enter up to 10 non-negative integers \\(-1 to terminate\\)\\:"  # timeout: 2
        - send: "2 3 4 5 6 7 8 9 10 11"
        - expect: "\r\nEnter your choice \\(1 for alternating sum or 2 for alternating division\\)\\:"  # timeout: 2
        - send: "2"
        - expect: "The result is 0.37\r\n"  # timeout: 2
    exit: 0

- case5:
    run: ./q2
    points: 5
    script:
        - expect: "Enter up to 10 non-negative integers \\(-1 to terminate\\)\\:"  # timeout: 2
        - send: "2 3 4 5 6 -1"
        - expect: "\r\nEnter your choice \\(1 for alternating sum or 2 for alternating division\\)\\:"  # timeout: 2
        - send: "1"
        - expect: "The result is 4.00\r\n"  # timeout: 2
    exit: 0

- case6:
    run: ./q2
    points: 5
    script:
        - expect: "Enter up to 10 non-negative integers \\(-1 to terminate\\)\\:"  # timeout: 2
        - send: "2 3 4 5 6 -1"
        - expect: "\r\nEnter your choice \\(1 for alternating sum or 2 for alternating division\\)\\:"  # timeout: 2
        - send: "2"
        - expect: "The result is 3.20\r\n"  # timeout: 2
    exit: 0

- case7:
    run: ./q2
    points: 5
    script:
        - expect: "Enter up to 10 non-negative integers \\(-1 to terminate\\)\\:"  # timeout: 2
        - send: "2 -1"
        - expect: "\r\nEnter your choice \\(1 for alternating sum or 2 for alternating division\\)\\:"  # timeout: 2
        - send: "1"
        - expect: "The result is 2.00\r\n"  # timeout: 2
    exit: 0

- case8:
    run: ./q2
    points: 5
    script:
        - expect: "Enter up to 10 non-negative integers \\(-1 to terminate\\)\\:"  # timeout: 2
        - send: "2 -1"
        - expect: "\r\nEnter your choice \\(1 for alternating sum or 2 for alternating division\\)\\:"  # timeout: 2
        - send: "2"
        - expect: "The result is 2.00\r\n"  # timeout: 2
    exit: 0

- case9:
    run: ./q2
    points: 5
    script:
        - expect: "Enter up to 10 non-negative integers \\(-1 to terminate\\)\\:"  # timeout: 2
        - send: "2 0 2 2 -1"
        - expect: "\r\nEnter your choice \\(1 for alternating sum or 2 for alternating division\\)\\:"  # timeout: 2
        - send: "1"
        - expect: "The result is 2.00\r\n"  # timeout: 2
    exit: 0

- case10:
    run: ./q2
    points: 5
    script:
        - expect: "Enter up to 10 non-negative integers \\(-1 to terminate\\)\\:"  # timeout: 2
        - send: "0 3 1 -1"
        - expect: "\r\nEnter your choice \\(1 for alternating sum or 2 for alternating division\\)\\:"  # timeout: 2
        - send: "2"
        - expect: "The result is 0.00\r\n"  # timeout: 2
    exit: 0
