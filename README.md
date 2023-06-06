# Synchronized TCP Server

This is a simple implementation of a synchronized TCP server using Boost.Asio library in C++. The server allows multiple clients to connect and exchange messages in a synchronized manner.

## Features

- Synchronized message broadcasting: When a client sends a message to the server, the server broadcasts the message to all connected clients in a synchronized manner.
- Multi-client support: The server can handle multiple client connections concurrently.
- Asynchronous I/O: The server and clients utilize Boost.Asio library to perform asynchronous I/O operations, ensuring efficient and non-blocking network communication.

## Requirements

- C++ compiler that supports C++11 or later
- Boost.Asio library

## Usage

<span style="color: red;">1.</span> Clone the repository: ``` https://github.com/MaksimSinyu/Synchronized-TCP-Server.git ```
<span style="color: red;">2.</span> Build the project <span style="color: blue;">using</span> the provided Makefile:
