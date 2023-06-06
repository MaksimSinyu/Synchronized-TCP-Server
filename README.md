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

1. Clone the repository: 
``` https://github.com/MaksimSinyu/Synchronized-TCP-Server.git ```
2. Build the project using the provided Makefile:
```cd synchronized-tcp-server```
```make```
3. Run the server:
```./server```
4. Connect multiple clients to the server using telnet or any TCP client of your choice:
```telnet localhost 1234```
5. Start sending messages from the connected clients. The server will receive each message and broadcast it to all other connected clients.

## License

This project is licensed under the Boost Software [LICENSE](https://github.com/MaksimSinyu/Synchronized-TCP-Server/blob/main/LICENSE) - Version 1.0. See the LICENSE file for details.

Feel free to explore, modify, and use the code for your own projects.

## Acknowledgements

This project utilizes the Boost.Asio library, which provides a powerful set of tools for network programming in C++.

## Contributing

Contributions are welcome! If you find any issues or have suggestions for improvement, please open an issue or submit a pull request.
