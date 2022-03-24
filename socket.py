import socket
import sys

def server_program():
    host = socket.gethostname()
    host_ip = socket.gethostbyname(host)

    print("Host name: ", str(host));
    print("Host IP: ", str(host_ip));

    if(len(sys.argv) != 2):
        print("Usage: python server.py <port_number>")
        sys.exit();

    port = int(sys.argv[1])

    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    server_socket.bind(('',port))

    server_socket.listen(5)
    
    while True:
        conn_socket, address =  server_socket.accept()

        print("Connection made from ", str(address))
        
        data = conn_socket.recv(1024).decode()
        if not data:
            print("Connection closed")
        else:
            print("Data from client: ", str(data))
            data = str(data).upper()
            conn_socket.send(data.encode());
            conn_socket.close()

if __name__ == '__main__':
    server_program()
