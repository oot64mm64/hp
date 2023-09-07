# socket-client.py
#call like python set_Blink_Rate.py R
#with R as first argument

import socket
import sys

if __name__ == "__main__":
    print(f"Arguments count: {len(sys.argv)}")
    for i, arg in enumerate(sys.argv):
        print(f"Argument {i:>6}: {arg}")

print(f"Name of the script      : {sys.argv[0]}")

print(f"Arguments of the script : {sys.argv[1:]}")


HOST = "10.13.37.179"  # D1mini #1 DNS locked address
PORT = 8888  # Heat_Pump project port

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))
    s.send(sys.argv[1].encode())
    data = s.recv(1024)
    print(f"Received {data!r}")
