# socket-client.py

import socket

HOST = "10.13.37.179"  # The server's hostname or IP address
PORT = 8888  # The port used by the server

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))
    s.sendall(b"M500")
    data = s.recv(1024)
    print(f"Received {data!r}")

    while True:
        True == True
