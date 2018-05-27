all: clienteFTP servidorFTP

clean: 
	rm -rf *.o;
	rm -rf clienteFTP;
	rm -rf servidorFTP;

clienteFTP: clienteFTP.o tp_socket.o Packet.o
	gcc -o clienteFTP tp_socket.o Packet.o clienteFTP.o

servidorFTP: servidorFTP.o tp_socket.o Packet.o List.o
	gcc -o servidorFTP tp_socket.o Packet.o List.o servidorFTP.o 

tp_socket.o: tp_socket.c
	gcc -c tp_socket.c -o tp_socket.o

Packet.o: Packet.c
	gcc -c Packet.c -o Packet.o

clienteFTP.o: clienteFTP.c
	gcc -c -w clienteFTP.c -o clienteFTP.o

servidorFTP.o: servidorFTP.c
	gcc -c -w servidorFTP.c -o servidorFTP.o

List.o: List.c
	gcc -c List.c -o List.o

