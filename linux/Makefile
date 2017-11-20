all:
	gcc server.c -o server -ansi -Wall
	gcc client.c -o client -ansi -Wall

temp:	temp_socket.c
	gcc temp_socket.c -o temp_socket

server:
	gcc server.c -o server -ansi -Wall
server_2:
	gcc server_2.c -o server -ansi -Wall
client:
	gcc client.c -o client -ansi -Wall

clean:
	rm -f server client temp_socket
