- init:
    run: rm -f fq2
    blocker: true

- build:
    run: gcc -std=c99 -Wall -Werror fq2.c -o fq2  # timeout: 10
    blocker: true

- case1:
    run: ./fq2
    points: 1
    script:
        - expect: "Enter data file name\\: "  # timeout: 2
        - send: "data"
        - expect: "Enter 1 to search for data, 2 to insert student record \\(0 to exit\\)\\: "  # timeout: 2
        - send: "1"
        - expect: "   Enter student id to search\\: " # timeout: 2
        - send: "5"
        - expect: "   1\\. Name\\: ayse\\, GPA\\: 4.10\r\n" # timeout: 2
        - expect: "Found 1 occurrences\\!\r\n" # timeout: 2
        - expect: "Enter 1 to search for data, 2 to insert student record \\(0 to exit\\)\\: "  # timeout: 2
        - send: "0"
    exit: 0

- case2:
    run: ./fq2
    points: 1
    script:
        - expect: "Enter data file name\\: "  # timeout: 2
        - send: "data"
        - expect: "Enter 1 to search for data, 2 to insert student record \\(0 to exit\\)\\: "  # timeout: 2
        - send: "1"
        - expect: "   Enter student id to search\\: " # timeout: 2
        - send: "1"
        - expect: "   1\\. Name\\: ali\\, GPA\\: 2.50\r\n" # timeout: 2
        - expect: "   2\\. Name\\: veli\\, GPA\\: 4.00\r\n" # timeout: 2
        - expect: "Found 2 occurrences\\!\r\n" # timeout: 2
        - expect: "Enter 1 to search for data, 2 to insert student record \\(0 to exit\\)\\: "  # timeout: 2
        - send: "0"
    exit: 0

- case3:
    run: ./fq2
    points: 1
    script:
        - expect: "Enter data file name\\: "  # timeout: 2
        - send: "data"
        - expect: "Enter 1 to search for data, 2 to insert student record \\(0 to exit\\)\\: "  # timeout: 2
        - send: "2"
        - expect: "   Student id\\: " # timeout: 2
        - send: "3"
        - expect: "   Student name\\: " # timeout: 2
        - send: "cihan"
        - expect: "   Student gpa\\: " # timeout: 2
        - send: "2.87"
        - expect: "Enter 1 to search for data, 2 to insert student record \\(0 to exit\\)\\: "  # timeout: 2		
        - send: "1"
        - expect: "   Enter student id to search\\: " # timeout: 2
        - send: "3"
        - expect: "   1\\. Name\\: cihan\\, GPA\\: 2.87\r\n" # timeout: 2
        - expect: "Found 1 occurrences\\!\r\n" # timeout: 2
        - expect: "Enter 1 to search for data, 2 to insert student record \\(0 to exit\\)\\: "  # timeout: 2
        - send: "0"
    exit: 0

- case4:
    run: ./fq2
    points: 1
    script:
        - expect: "Enter data file name\\: "  # timeout: 2
        - send: "data"
        - expect: "Enter 1 to search for data, 2 to insert student record \\(0 to exit\\)\\: "  # timeout: 2
        - send: "1"
        - expect: "   Enter student id to search\\: " # timeout: 2
        - send: "7"
        - expect: "Found 0 occurrences\\!\r\n" # timeout: 2
        - expect: "Enter 1 to search for data, 2 to insert student record \\(0 to exit\\)\\: "  # timeout: 2
        - send: "0"
    exit: 0

- case5:
    run: ./fq2
    points: 1
    script:
        - expect: "Enter data file name\\: "  # timeout: 2
        - send: "datam"
        - expect: "Enter 1 to search for data, 2 to insert student record \\(0 to exit\\)\\: "  # timeout: 2
        - send: "1"
        - expect: "   Enter student id to search\\: " # timeout: 2
        - send: "1"
        - expect: "Could not open file\\!\r\n"  # timeout: 2
    exit: 1