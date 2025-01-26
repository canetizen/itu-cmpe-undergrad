- init:
    run: rm -f vector
    blocker: true

- build:
    run: gcc -std=c99 -Wall -Werror vector.c -lm -o vector  # timeout: 2
    blocker: true

- case1:
    run: ./vector
    points: 1
    script:
        - expect: "Enter vec1\\:"  # timeout: 2
        - send: "2 2"
        - expect: "Enter vec2\\:"  # timeout: 2
        - send: "3 5"
        - expect: "2i \\+ 2j\r\n"  # timeout: 2
        - expect: "3i \\+ 5j\r\n"  # timeout: 2
        - expect: "vec1 \\- vec2 = \\-1i \\+ -3j\r\n"  # timeout: 2
        - expect: "vec1 \\+ vec2 = 5i \\+ 7j\r\n"  # timeout: 2
        - expect: "Angle of vec1\\: 0.785398\r\n"  # timeout: 2
        - expect: "Angle of vec2\\: 1.030377\r\n"  # timeout: 2
        - expect: "Angle between vec1 and vec2\\: 0.244979\r\n"  # timeout: 2
        - expect: "Magnetude of vec1 : 2.828427\r\n"  # timeout: 2		
        - expect: "Magnetude of vec2 : 5.830952\r\n"  # timeout: 2	
        - expect: "vec1 \\* vec2 = 16\r\n"  # timeout: 2
    exit: 0