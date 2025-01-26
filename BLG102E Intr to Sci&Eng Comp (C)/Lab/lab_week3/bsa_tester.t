- init:
    run: rm -f bsa
    blocker: true

- build:
    run: gcc -std=c99 -Wall -Werror bsa.c -lm -o bsa  # timeout: 2
    blocker: true

- case_cihan:
    run: ./bsa
    points: 10
    script:
        - expect: "Input height\\(cm\\) and weight\\(g\\):"  # timeout: 2
        - send: "175"
        - send: "98000"
        - expect: "BSA: 2.22\r\n"                   # timeout: 2
        - expect: _EOF_  # timeout: 2
    exit: 0

- case_ronaldo:
    run: ./bsa
    points: 10
    script:
        - expect: "Input height\\(cm\\) and weight\\(g\\):"  # timeout: 2
        - send: "185"
        - send: "85000"
        - expect: "BSA: 2.09\r\n"                   # timeout: 2
        - expect: _EOF_  # timeout: 2
    exit: 0

- case_ciroz:
    run: ./bsa
    points: 10
    script:
        - expect: "Input height\\(cm\\) and weight\\(g\\):"  # timeout: 2
        - send: "155"
        - send: "45000"
        - expect: "BSA: 1.40\r\n"                   # timeout: 2
        - expect: _EOF_  # timeout: 2
    exit: 0