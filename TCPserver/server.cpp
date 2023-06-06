#include <iostream>
#include <boost/asio.hpp>
#include <vector>
#include <thread>
#include <chrono>

using boost::asio::ip::tcp;

class Session : public std::enable_shared_from_this<Session> {
public:
    Session(tcp::socket socket, std::vector<std::shared_ptr<Session>>& sessions)
        : socket_(std::move(socket)), sessions_(sessions)
    {
    }

    void start()
    {
        sessions_.push_back(shared_from_this());
        doRead();
    }

    void sendMessageToClients(const std::string& message)
    {
        std::lock_guard<std::mutex> lock(sessionsMutex_);
        for (auto& session : sessions_) {
            boost::asio::write(session->socket_, boost::asio::buffer(message + '\n'));
        }
    }

private:
    void doRead()
    {
        auto self(shared_from_this());
        boost::asio::async_read_until(socket_, buffer_, '\n',
            [this, self](boost::system::error_code ec, std::size_t /*length*/)
            {
                if (!ec)
                {
                    std::string message(std::istreambuf_iterator<char>(&buffer_), {});
                    buffer_.consume(buffer_.size());
                    std::cout << "Server: Received message: " << message;

                    // Measure time before synchronization
                    auto start = std::chrono::high_resolution_clock::now();

                    sendMessageToClients(message);

                    // Measure time after synchronization
                    auto end = std::chrono::high_resolution_clock::now();
                    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
                    std::cout << "Server: Message has been sent. Synchronized in " << duration << " milliseconds." << std::endl;

                    doRead();
                }
            });
    }

    tcp::socket socket_;
    boost::asio::streambuf buffer_;
    std::vector<std::shared_ptr<Session>>& sessions_;
    std::mutex sessionsMutex_;
};

class Server {
public:
    Server(boost::asio::io_context& ioContext, short port)
        : acceptor_(ioContext, tcp::endpoint(tcp::v4(), port))
    {
        startAccept();
    }

private:
    void startAccept()
    {
        acceptor_.async_accept(
            [this](boost::system::error_code ec, tcp::socket socket)
            {
                if (!ec)
                {
                    std::cout << "Server: Accepted connection from " << socket.remote_endpoint() << std::endl;
                    std::make_shared<Session>(std::move(socket), sessions_)->start();
                }

                startAccept();
            });
    }

    tcp::acceptor acceptor_;
    std::vector<std::shared_ptr<Session>> sessions_;
};

class Client {
public:
    Client(boost::asio::io_context& ioContext, const std::string& host, short port)
        : socket_(ioContext)
    {
        tcp::resolver resolver(ioContext);
        boost::asio::connect(socket_, resolver.resolve(host, std::to_string(port)));
    }

    void start()
    {
        std::string message;
        while (std::getline(std::cin, message)) {
            sendMessage(message);
        }
    }

    void sendMessage(const std::string& message)
    {
        boost::asio::write(socket_, boost::asio::buffer(message + '\n'));
    }

private:
    tcp::socket socket_;
};

int main()
{
    boost::asio::io_context ioContext;

    Server server(ioContext, 1234);
    Client firstClient(ioContext, "localhost", 1234);
    Client secondClient(ioContext, "localhost", 1234);

    std::thread serverThread([&ioContext]() { ioContext.run(); });
    std::thread firstClientThread([&firstClient]() { firstClient.start(); });
    std::thread secondClientThread([&secondClient]() { secondClient.start(); });

    serverThread.join();
    firstClientThread.join();
    secondClientThread.join();

    return 0;
}
