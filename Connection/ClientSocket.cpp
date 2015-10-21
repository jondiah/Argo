// Implementation of the ClientSocket class

#include "ClientSocket.h"
#include "SocketException.h"
#include <QDebug>


ClientSocket::ClientSocket ( std::string host, int port )
{
    m_port = port;
    m_host = host;
}

bool ClientSocket::createConnection()
{
    bool status = Socket::create();
    if ( ! status )
    {
        qDebug() << "Could not create client socket.";
    }
    return status;
}

bool ClientSocket::connectToHost()
{
    bool status = Socket::connect ( m_host, m_port );
    if ( !status )
    {
        qDebug() << "Could not bind to port.";
    }
    return status;
}

bool ClientSocket::closeConnection()
{
    Socket::closeConnection();
}

const ClientSocket& ClientSocket::operator << ( const std::string& s ) const
{
    if ( ! Socket::send ( s ) )
    {
        throw SocketException ( "Could not write to socket." );
    }

    return *this;

}


const ClientSocket& ClientSocket::operator >> ( std::string& s ) const
{
    if ( ! Socket::recv ( s ) )
    {
        throw SocketException ( "Could not read from socket." );
    }

    return *this;
}
