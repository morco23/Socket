#ifndef __MORCOHEN_SOCKET_HPP__
#define __MORCOHEN_SOCKET_HPP__

#include <sys/socket.h> //sockaddr
#include <memory>       //shared_ptr

/***********************************************************************
This class makes the working with socket in the style of object oriented.
It is also support resource managment, so you can be confident the socket
will be freed in the end of program.
To get information about of the function, you can read the man page
of the equivalent function. (ctor- socket, bind, listen, recv, recvfrom,
send, sendto).
the function setBlock makes the socket to perform in blocking/nonblocking
mode, according to the input.
This code will be work in c++ 11 and up.
************************************************************************/

namespace morcohen
{

class Socket
{
public:
    explicit Socket(int domain_, int type_, int protocol_);
    ~Socket() noexcept;
    void Bind(int port_);
    void Bind(sockaddr *addr_, socklen_t addrlen_);
    void Listen(int maxPending_);
    std::shared_ptr<Socket> Accept(sockaddr *address_, socklen_t *addressLen_);
    ssize_t Recieve(void *buf_, std::size_t len_, int flags);
    ssize_t RecieveFrom(void *buf_, std::size_t len_, int flags,
                        struct sockaddr *srcAddr, socklen_t *addrLen);
    ssize_t Send(const void *buf, size_t len, int flags); 
    ssize_t SendTo(const void *buf, size_t len, int flags,
                      const struct sockaddr *destAdd, socklen_t addrlen);
    void Close();
    void SetBlock(bool isBlock);
    int GetFd() const noexcept;
private:
    Socket(const Socket&) = delete;
    Socket& operator=(const Socket&) = delete;

    explicit Socket(int fd_) noexcept;
    int CreateSocket(int domain_, int type_, int protocol_);
    int m_fd;
    bool m_wasClosed;
};

}//morcohen

#endif //__MORCOHEN_SOCKET_HPP__