- init:
    run: rm -f m2q1
    blocker: true

- build:
    run: gcc -std=c99 -Wall -Werror m2q1.c -o m2q1  # timeout: 2
    blocker: true

- case 1:
    run: ./m2q1
    points: 1
    script:
        - expect: "Insert 20 consecutive characters:"  # timeout: 2
        - send: "0abc456789012345def9"
        - expect: "\r\nThe user entered the following characters:"  # timeout: 2
        - expect: "0abc456789012345def9\r\n"  # timeout: 2
        - expect: "The characters in reverse order are: "  # timeout: 2
        - expect: "9fed543210987654cba0\r\n"  # timeout: 2
    exit: 0

- case 2:
    run: ./m2q1
    points: 1
    script:
        - expect: "Insert 20 consecutive characters:"  # timeout: 2
        - send: "a1b2c3d4e5f6g7h8i\n\n\n"
        - expect: "\r\nThe user entered the following characters:"  # timeout: 2
        - expect: "a1b2c3d4e5f6g7h8i\r\n\r\n\r\n\r\n"  # timeout: 2
        - expect: "The characters in reverse order are: "  # timeout: 2
        - expect: "\r\n\r\n\r\ni8h7g6f5e4d3c2b1a\r\n"  # timeout: 2
    exit: 0

- case 3:
    run: ./m2q1
    points: 1
    script:
        - expect: "Insert 20 consecutive characters:"  # timeout: 2
        - send: "0 1 2 ITU 1773 BEE 3 4 5 6"
        - expect: "\r\nThe user entered the following characters:"  # timeout: 2
        - expect: "0 1 2 ITU 1773 BEE 3\r\n"  # timeout: 2
        - expect: "The characters in reverse order are: "  # timeout: 2
        - expect: "3 EEB 3771 UTI 2 1 0\r\n"  # timeout: 2
    exit: 0
