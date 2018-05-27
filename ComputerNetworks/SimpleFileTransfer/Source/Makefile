all: clienteFTP servidorFTP

clean: 
	rm -rf *.o;
	rm -rf clienteFTP;
	rm -rf servidorFTP;
	
clienteFTP: clienteFTP.c
	gcc -w clienteFTP.c -o clienteFTP

servidorFTP: servidorFTP.c
	gcc -w servidorFTP.c -o servidorFTP

