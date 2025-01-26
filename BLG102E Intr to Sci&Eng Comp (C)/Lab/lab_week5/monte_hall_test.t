- init:
    run: rm -f monte_hall_sim
    blocker: true

- build:
    run: gcc -std=c99 -Wall -Werror monte_hall.c -o monte_hall_sim  # timeout: 2
    blocker: true

- case:
    run: ./monte_hall_sim
    points: 1
    script:
        - expect: "win ratio for strategy 1: 0.333\r\n"  # timeout: 2
        - expect: "win ratio for strategy 2: 0.667\r\n"                   # timeout: 2
        - expect: _EOF_  # timeout: 2
    exit: 0