### Local chat made with c++ to get knowledge about sockets and threads, using concurrency
This is a pretty basic CLI message app that uses sockets to realtime chat between two or more terminals using sockets

### how this works
the server binds the socket with the IP and listens on the port defined with an infinite loop listening all the time, when a client joins the server creates a new thread.

the client creates the socket and try to connect to the server, when the server accept the connections then the user can type a massage and wait for response.

### Why
Just to practice with C++ and sockets and threads this will help to improve my skills and knowledge.

### How to use
Make sure your have Clang++ in your sistem

First need to execute the `compile_client` and `compile_server` to compile and execute both client and server.


    
