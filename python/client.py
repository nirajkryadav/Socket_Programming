import socket

host = raw_input("Enter IP address: ")
port = 8088

MSG= raw_input("Enter message:")
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((host, port))

s.send(MSG)

print s.recv(1024)
s.close
