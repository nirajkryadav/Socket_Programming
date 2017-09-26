import socket
import sys


port = 8088
host = '127.0.0.1'
BUFFER_SIZE = 20

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)


try:
	s.bind((host, port))
except socket.error, msg:
	print ('Binding failed : ' + str(msg[0]) + ' Message ' + msg[1])
	sys.exit()
print ('Socket binding completed')

s.listen(5)
print ('Socket now listening')
conn, addr = s.accept()
while True:
    data = conn.recv(BUFFER_SIZE)
    if not data: break
    print ("Message from client: "+ data)
    conn.send(data)
conn.close()
