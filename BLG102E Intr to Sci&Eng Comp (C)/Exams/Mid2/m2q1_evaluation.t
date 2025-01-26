- init:
    run: rm -f m2q1
    blocker: true

- build:
    run: gcc -std=c99 -Wall -Werror m2q1.c -o m2q1  # timeout: 2
    blocker: true

- case full_number:
    run: ./m2q1
    points: 7
    script:
        - expect: "Insert 20 consecutive characters:"  # timeout: 2
        - send: "15396630804392840547"
        - expect: "\r\nThe user entered the following characters:"  # timeout: 2
        - expect: "15396630804392840547\r\n"  # timeout: 2
        - expect: "The characters in reverse order are: "  # timeout: 2
        - expect: "74504829340803669351\r\n"  # timeout: 2
    exit: 0

- case full_letter:
    run: ./m2q1
    points: 7
    script:
        - expect: "Insert 20 consecutive characters:"  # timeout: 2
        - send: "abcdefghijklmnoprstu"
        - expect: "\r\nThe user entered the following characters:"  # timeout: 2
        - expect: "abcdefghijklmnoprstu\r\n"  # timeout: 2
        - expect: "The characters in reverse order are: "  # timeout: 2
        - expect: "utsrponmlkjihgfedcba\r\n"  # timeout: 2
    exit: 0

- case full_random:
    run: ./m2q1
    points: 7
    script:
        - expect: "Insert 20 consecutive characters:"  # timeout: 2
        - send: "abc123ghi**jk-12lm45"
        - expect: "\r\nThe user entered the following characters:"  # timeout: 2
        - expect: "abc123ghi\\*\\*jk-12lm45\r\n"  # timeout: 2
        - expect: "The characters in reverse order are: "  # timeout: 2
        - expect: "54ml21-kj\\*\\*ihg321cba\r\n"  # timeout: 2
    exit: 0

- case less_letter_newline:
    run: ./m2q1
    points: 5
    script:
        - expect: "Insert 20 consecutive characters:"  # timeout: 2
        - send: "123456789a\n\n\n\n\n\n\n\n\n\n"
        - expect: "\r\nThe user entered the following characters:"  # timeout: 2
        - expect: "123456789a\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n"  # timeout: 2
        - expect: "The characters in reverse order are: "  # timeout: 2
        - expect: "\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\na987654321\r\n"  # timeout: 2
    exit: 0

- case less_letter_spaces:
    run: ./m2q1
    points: 4
    script:
        - expect: "Insert 20 consecutive characters:"  # timeout: 2
        - send: "abcdefghijkl        "
        - expect: "\r\nThe user entered the following characters:"  # timeout: 2
        - expect: "abcdefghijkl        \r\n"  # timeout: 2
        - expect: "The characters in reverse order are: "  # timeout: 2
        - expect: "        lkjihgfedcba\r\n"  # timeout: 2
    exit: 0

- case less_letter_tabs:
    run: ./m2q1
    points: 4
    script:
        - expect: "Insert 20 consecutive characters:"  # timeout: 2
        - send: "123456789a\t\t\t\t\t\t\t\t\t\t"
        - expect: "\r\nThe user entered the following characters:"  # timeout: 2
        - expect: "123456789a\t\t\t\t\t\t\t\t\t\t\r\n"  # timeout: 2
        - expect: "The characters in reverse order are: "  # timeout: 2
        - expect: "\t\t\t\t\t\t\t\t\t\ta987654321\r\n"  # timeout: 2
    exit: 0

- case more_newline_23:
    run: ./m2q1
    points: 5
    script:
        - expect: "Insert 20 consecutive characters:"  # timeout: 2
        - send: " abc123def456ghi789*=\n\n"
        - expect: "\r\nThe user entered the following characters:"  # timeout: 2
        - expect: " abc123def456ghi789\\*\r\n"  # timeout: 2
        - expect: "The characters in reverse order are: "  # timeout: 2
        - expect: "\\*987ihg654fed321cba \r\n"  # timeout: 2
    exit: 0

- case more_random_23:
    run: ./m2q1
    points: 4
    script:
        - expect: "Insert 20 consecutive characters:"  # timeout: 2
        - send: "a*3! k4ldn+e    syw6rit"
        - expect: "\r\nThe user entered the following characters:"  # timeout: 2
        - expect: "a\\*3! k4ldn\\+e    syw6\r\n"  # timeout: 2
        - expect: "The characters in reverse order are: "  # timeout: 2
        - expect: "6wys    e\\+ndl4k !3\\*a\r\n"  # timeout: 2
    exit: 0

- case more_spaces_30:
    run: ./m2q1
    points: 4
    script:
        - expect: "Insert 20 consecutive characters:"  # timeout: 2
        - send: "         a         a          "
        - expect: "\r\nThe user entered the following characters:"  # timeout: 2
        - expect: "         a         a\r\n"  # timeout: 2
        - expect: "The characters in reverse order are: "  # timeout: 2
        - expect: "a         a         \r\n"  # timeout: 2
    exit: 0

- case single_inputs:
    run: ./m2q1
    points: 3
    script:
        - expect: "Insert 20 consecutive characters:"  # timeout: 2
        - send: "a"
        - expect: ""  # timeout: 1
        - send: "\n"
        - expect: ""  # timeout: 1
        - send: "b"
        - expect: ""  # timeout: 1
        - send: "a"
        - expect: ""  # timeout: 1
        - send: "\n"
        - expect: ""  # timeout: 1
        - send: "b"
        - expect: ""  # timeout: 1
        - send: "a"
        - expect: ""  # timeout: 1
        - send: "\n"
        - expect: ""  # timeout: 1
        - send: "b"
        - expect: ""  # timeout: 1
        - send: "a"
        - expect: "\r\nThe user entered the following characters:"  # timeout: 2
        - expect: "a\r\n\r\n\r\nb\r\na\r\n\r\n\r\nb\r\na\r\n\r\n\r\nb\r\na\r\n\r\n"  # timeout: 2
        - expect: "The characters in reverse order are: "  # timeout: 2
        - expect: "\r\na\r\nb\r\n\r\n\r\na\r\nb\r\n\r\n\r\na\r\nb\r\n\r\n\r\na\r\n"  # timeout: 2
    exit: 0
