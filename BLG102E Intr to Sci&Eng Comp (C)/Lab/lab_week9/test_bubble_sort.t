- init:
    run: rm -f bubble_sort
    blocker: true

- build:
    run: gcc -std=c99 -Wall -Werror bubble_sort2.c -o bubble_sort  # timeout: 2
    blocker: true

- case1:
    run: ./bubble_sort
    points: 1
    script:
        - expect: "Enter 10 numbers\\:"  # timeout: 2
        - send: "6 2 5 7 1 3 9 4 8 0"
        - expect: "Original Array\\: 6 2 5 7 1 3 9 4 8 0\r\n"  # timeout: 2
        - expect: "Sorted Array\\(Ascending\\)\\: 0 1 2 3 4 5 6 7 8 9\r\n"  # timeout: 2
        - expect: "Sorted Array\\(Descending\\)\\: 9 8 7 6 5 4 3 2 1 0\r\n"  # timeout: 2
    exit: 0

- case2:
    run: ./bubble_sort
    points: 1
    script:
        - expect: "Enter 10 numbers\\:"  # timeout: 2
        - send: "7 12 54 27 11 37 92 64 18 30"
        - expect: "Original Array\\: 7 12 54 27 11 37 92 64 18 30\r\n"  # timeout: 2
        - expect: "Sorted Array\\(Ascending\\)\\: 7 11 12 18 27 30 37 54 64 92\r\n"  # timeout: 2
        - expect: "Sorted Array\\(Descending\\)\\: 92 64 54 37 30 27 18 12 11 7\r\n"  # timeout: 2
    exit: 0
