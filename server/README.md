# UI-ACOM
## Summary
	This program is designed to run as a client server setup on the Raspberry Pi and a AWS server instance. This program is a dummy example to make a connection using TCP sockets. It transfers a message and echos it back between the client and server.

## Development
### Client
	The client program imports socket and creates a socket. The socket is then connected to the port where the server is listening for. Once a connection is established, the client will send whatever data message it has, in this case the example test was the simple message ‘ This is the message. It will be repeated.’ After the message is sent, the client waits for a response before closing the socket connection.
### Server 
	The server program also imports socket and begins by creating a new socket. It then binds the socket to a port and the server’s IP address. The server then waits for a connection attempt from the client. once the connection is made the server receives the data in small chunks and echos back the message. Once the end of the message has been reached the socket connection is closed. 
	In actual communication, the server wouldn’t echo back the message, this was just done for testing purposes.
		
