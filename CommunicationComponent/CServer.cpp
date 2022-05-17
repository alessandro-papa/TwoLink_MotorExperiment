/**
 * @file	CServer.cpp
 * @author	Michael Meindl
 * @date	28.9.2016
 * @brief	Class defintions for CServer.
 */
#include "CServer.h"
#include "Global.h"
#include "Assertion.h"
#include <unistd.h>		//close()
#include <strings.h>	//bzero()
#include <iostream>
#include <errno.h>

extern int errno;

bool CServer::receiveMessage(CMessage& msg)
{
	bool success = false;
	Int32 retVal = -1;
	size_t bytesReceived = 0;
	UInt8* buffer = reinterpret_cast<UInt8*>(&msg);
	do
	{
		// read from buffer
		// read() is API --> interface to operating system
		// blocking read(): if there is no msg thread will sleep until new message is in buffer
		retVal = read(mConnectedSocketFD, (buffer+bytesReceived), sizeof(msg)-bytesReceived);

		if(retVal < 0)
		{
			switch(errno)
			{
				case ECONNRESET:
					success = false;
					break;
				default:
					sAssertion(retVal >= 0,
							"(CServer::receiveMessage()): Failed to read from the socket", true);
					break;
			}
			break;
		}
		else if(retVal == 0)
		{
			success = false;
			break;
		}
		else
		{
			bytesReceived += retVal;
		}
	}while(bytesReceived < sizeof(msg));

	if(bytesReceived == sizeof(msg))
	{
		success = true;
	}
	return success;
}
bool CServer::transmitMessage(const CMessage& msg)
{
	bool success = false;
	Int32 retVal = -1;
	size_t writtenByte = 0;
	const UInt8* buffer = reinterpret_cast<const UInt8*>(&msg);
	do
	{
		// send message to buffer
		// send message and track written bytes via retVal
		// send() is unix API --> interface to operating system
		retVal = send(mConnectedSocketFD, (buffer+writtenByte), (sizeof(msg) - writtenByte), MSG_NOSIGNAL);
		if((retVal < 0) && (errno == EPIPE)) 	// if writing was not successfull and errno is broken pipe
		{
			std::cout << "[*] Server: Connection was terminated" << std::endl;
			success = false;
			break;
		}
		else if(retVal < 0) 	// if writing was not successfull
		{
			std::cout << "CServer::transmitMessage(): Failed to send the message, errno: " << errno << std::endl;
		}
		// if writing was successfull
		success = true;
		writtenByte += retVal;	// add retVal to written bytes
	}while(writtenByte < sizeof(msg));	// do as long as message was not written completely
	return success;
}
void CServer::init()
{
	mSocketFD = socket(AF_INET, SOCK_STREAM, 0);
	int enable = 1;
	setsockopt(mSocketFD, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int));
	sAssertion(mSocketFD >= 0, "(CServer::CServer()): Failed to open socket.", true);

	//Bind the socket to an address
	struct sockaddr_in server_addr;
	bzero(reinterpret_cast<Int8*>(&server_addr), sizeof(server_addr));
	server_addr.sin_family		= AF_INET;
	server_addr.sin_port		= htons(sPort);
	server_addr.sin_addr.s_addr = INADDR_ANY;
	// bind socket to allocate port for socket communication
	Int32 retVal = bind(mSocketFD,
						reinterpret_cast<struct sockaddr*>(&server_addr),
						sizeof(server_addr));
	sAssertion(retVal >= 0, "(CServer::CServer()): Failed to bind the socket.", true);

	retVal = listen(mSocketFD, 1);
	sAssertion(retVal >= 0, "(CServer::CServer()): Failed to listen().", true);
}
bool CServer::waitForClient()
{
	// wait for and accept connection request to socket mSocketFD from other process
	// save client socket fd in mConnectedSocketFD
	// save clientAddress in mClientAddr
	mConnectedSocketFD = accept(mSocketFD,
					   	   	    reinterpret_cast<struct sockaddr*>(&mClientAddr),
								&mClientLen);
	sAssertion(mConnectedSocketFD >= 0, "(CServer::CServer()): Failed to accept the client connection.", true);
	return true;
}
CServer::CServer() : mSocketFD(-1),
					 mConnectedSocketFD(-1),
					 mClientLen{0}
{

}
CServer::~CServer()
{
	Int32 retVal = shutdown(mConnectedSocketFD, SHUT_RDWR);
	sAssertion(retVal >= 0, "(CServer::~CServer()): Failed to shutdown socket.", true);

	retVal = close(mConnectedSocketFD);
	sAssertion(retVal >= 0, "(CServer::~CServer()): Failed to close connected socket.", true);

	retVal = close(mSocketFD);
	sAssertion(retVal >= 0, "(CServer::~CServer()): Failed to close socket.", true);
}
