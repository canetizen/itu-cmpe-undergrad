- init:
    run: rm -f pi_calculation
    blocker: true

- build:
    run: gcc -std=c99 -Werror pi_calculation.c -o pi_calculation  # timeout: 2
    blocker: true

- case1:
    run: ./pi_calculation
    points: 1
    script:
        - expect: "Mean Value of 100 Estimated Pi's = 3.1.."  # timeout: 2
    exit: 0
