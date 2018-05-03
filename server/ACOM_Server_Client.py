
import socket
import sys

# Create a TCP/IP socket
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Connect the socket to the port where the server is listening
server_address = ('18.217.97.174', 10000) #IP address of server and port
print('connection to server on port ', server_address)
sock.connect(server_address)
try:

    # Send data
    message = 'This is the message.  It will be repeated.'
    print('sending message ', message)
    sock.sendall(message)

    # Look for the response
    amount_received = 0
    amount_expected = len(message)

    while amount_received < amount_expected:
        data = sock.recv(16)
        amount_received += len(data)
        print('received data ', data)

finally:
    print('closing socket')
    sock.close()






