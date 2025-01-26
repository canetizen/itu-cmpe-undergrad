- init:
    run: rm -f fq1
    blocker: true

- build:
    run: gcc -std=c99 -Wall -Werror fq1.c -o fq1  # timeout: 10
    blocker: true

- case1:
    run: ./fq1
    points: 1
    script:
        - expect: "Enter 1 to 5 arguments!"  # timeout: 2
    exit: 1

- case2:
    run: ./fq1 cihan elif ziya yaren seymanur
    points: 1
    script:
        - expect: "Names should start with either M_ or F_!"  # timeout: 2
    exit: 1

- case3:
    run: ./fq1 M_cihan F_elif M_ziya F_yaren F_
    points: 1
    script:
        - expect: "Names should contain at least 1 character after gender prefix!"  # timeout: 2
    exit: 1

- case4:
    run: ./fq1 M_cihan F_elif M_ziya F_yaren F_seymanur
    points: 1
    script:
        - expect: "Female count: 3, avg. female name length: 5.7"
        - expect: "Male count: 2, avg. male name length: 4.5"   # timeout: 2
    exit: 0

- case5:
    run: ./fq1 F_ayse F_elif F_gamze F_yaren F_seymanur
    points: 1
    script:
        - expect: "Female count: 5, avg. female name length: 5.2"
        - expect: "Male count: 0, avg. male name length: 0"   # timeout: 2
    exit: 0