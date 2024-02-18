#include <SFML/Network.hpp>
#include <iostream>
#include <thread>

#define DEFAULT_PORT 3000

using namespace std;

void runServer(unsigned short port) {
    sf::TcpListener listener;

    if (listener.listen(port) != sf::Socket::Done) {
        cout << "could not listen" << endl;
        return;
    }
    cout << "listening on port: " << port << endl;

    sf::TcpSocket socket;
    if (listener.accept(socket) != sf::Socket::Done) {
        cout << "could not connect client" << endl;
        return;
    }
    cout << "client connected: " << socket.getRemoteAddress() << ":" << socket.getLocalPort() << endl;

    const char out[] = "hello world!";
    if (socket.send(out, sizeof(out)) != sf::Socket::Status::Done)
        return;
    cout << "message sent to the client: " << out << endl;
}

void runClient(unsigned short port) {
    sf::TcpSocket socket;

    if (socket.connect(sf::IpAddress::getLocalAddress(), port) != sf::Socket::Status::Done) {
        cout << "could not connect to server" << endl;
        return;
    }
    cout << "connected to server: " << socket.getRemoteAddress() << endl;

    char in[128];
    size_t received;
    if (socket.receive(in, sizeof(in), received) != sf::Socket::Status::Done)
        return;
    cout << "message received from the server: " << in << endl;
}

int main()
{
    int who;
    cin >> who;

    if (who) {
        runServer(DEFAULT_PORT);
    } else {
        runClient(DEFAULT_PORT);
    }

    return 0;
}