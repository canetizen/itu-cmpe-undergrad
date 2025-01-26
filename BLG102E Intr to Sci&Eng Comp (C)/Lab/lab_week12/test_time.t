- init:
    run: rm -f extended_time
    blocker: true

- build:
    run: gcc -std=c99 -Wall -Werror extended_time.c -o extended_time  # timeout: 2
    blocker: true

- case1:
    run: ./extended_time
    points: 1
    script:
        - expect: "Enter timeA:" # timeout: 2
        - send: 5 45 35
        - expect: "Enter dateA:" # timeout: 2
        - send: 1993 2 20
        - expect: "Enter timeB:" # timeout: 2
        - send: 2 45 20
        - expect: "Enter dateB:" # timeout: 2
        - send: 0 10 10
        - expect: "Extended Time is 30/12/1993 08\\:30\\:55\r\n"  # timeout: 2
        - expect: "Extended Time is 10/04/1992 03\\:00\\:15\r\n"  # timeout: 2
    exit: 0
