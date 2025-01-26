**RDT Over UDP**

This project implements a reliable data transfer protocol over UDP, similar to TCP's functionality but built from scratch. The implementation includes both client and server components that handle packet loss through the Selective Repeat protocol, with various window sizes (1, 10, 50, 100) and error rates (1\%, 5\%, 10\%, 20\%) to test protocol performance. The system establishes connections through a three-way handshake, manages packet timeouts, and ensures reliable data delivery despite using an unreliable UDP channel.
<a href='https://www.overleaf.com/read/ccmvtxbxsfpt#e10d07'>Click to view project report</a>
